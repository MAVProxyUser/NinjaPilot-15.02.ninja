#include "CameraView.hh"

#include <gz/gui/Application.hh>
#include <gz/plugin/Register.hh>

#include <QQmlEngine>
#include <QQmlContext>
#include <QQuickWindow>

using namespace ninjapilot;

QImage FrameProvider::requestImage(const QString &, QSize *_size, const QSize &)
{
  QMutexLocker lock(&this->mutex);
  if (_size)
    *_size = this->frame.size();
  return this->frame;
}

void FrameProvider::SetFrame(const QImage &_img)
{
  QMutexLocker lock(&this->mutex);
  this->frame = _img;
}

CameraView::CameraView() : gz::gui::Plugin()
{
}

CameraView::~CameraView() = default;

int CameraView::FrameId() const
{
  return this->frameId;
}

void CameraView::LoadConfig(const tinyxml2::XMLElement *_pluginElem)
{
  std::string topic;
  if (this->title.empty())
    this->title = "Camera";

  if (_pluginElem)
  {
    if (auto elem = _pluginElem->FirstChildElement("topic"))
      topic = elem->GetText() ? elem->GetText() : "";
  }
  if (topic.empty())
    topic = "/camera";

  // One provider per panel, named from the topic: three stacked cameras must
  // not share an image:// namespace or they all show the same frame.
  this->providerName = QString::fromStdString(topic);
  this->providerName.replace('/', '_');
  this->provider = new FrameProvider();
  gz::gui::App()->Engine()->addImageProvider(this->providerName,
                                             this->provider);
  this->PluginItem()->setProperty("providerName", this->providerName);

  this->node.Subscribe(topic, &CameraView::OnImage, this);
}

void CameraView::OnImage(const gz::msgs::Image &_msg)
{
  if (_msg.width() == 0 || _msg.height() == 0 || _msg.data().empty())
    return;

  // RGB_INT8 is what the SDF cameras publish (format R8G8B8). Anything else
  // is dropped rather than mis-rendered as garbage colour.
  if (_msg.pixel_format_type() != gz::msgs::PixelFormatType::RGB_INT8)
    return;

  QImage img(reinterpret_cast<const uchar *>(_msg.data().data()),
             _msg.width(), _msg.height(), 3 * _msg.width(),
             QImage::Format_RGB888);
  this->provider->SetFrame(img.copy());   // copy: _msg data dies on return
  ++this->frameId;
  emit this->FrameIdChanged();
}

GZ_ADD_PLUGIN(ninjapilot::CameraView, gz::gui::Plugin)
