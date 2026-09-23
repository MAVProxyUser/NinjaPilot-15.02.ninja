#include "CameraView.hh"

#include <algorithm>
#include <cstdint>

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

  // RGB_INT8 is what the SDF's RGB cameras publish (format R8G8B8). L_INT16
  // is what a thermal camera publishes (SDF <format>L16</format> - one
  // 16-bit temperature-derived intensity per pixel, no colour channels at
  // all) - a fixed RGB_INT8-only check silently dropped every thermal frame
  // and looked exactly like "no signal" even though the sensor was
  // publishing real data the whole time. Anything else is still dropped
  // rather than mis-rendered as garbage.
  const auto width = _msg.width();
  const auto height = _msg.height();

  if (_msg.pixel_format_type() == gz::msgs::PixelFormatType::RGB_INT8)
  {
    QImage img(reinterpret_cast<const uchar *>(_msg.data().data()),
               width, height, 3 * width, QImage::Format_RGB888);
    this->provider->SetFrame(img.copy());   // copy: _msg data dies on return
    ++this->frameId;
    emit this->FrameIdChanged();
    return;
  }

  if (_msg.pixel_format_type() == gz::msgs::PixelFormatType::L_INT16)
  {
    const auto *raw = reinterpret_cast<const uint16_t *>(_msg.data().data());
    const size_t count = static_cast<size_t>(width) * height;
    if (_msg.data().size() < count * sizeof(uint16_t))
      return;

    // Per-frame min/max normalisation to 8-bit grayscale: this is a
    // display convenience (self-scaling contrast, like a real thermal
    // camera's auto-gain), not a measurement - there is no fixed
    // temperature-to-brightness mapping here.
    uint16_t lo = 0xFFFF, hi = 0;
    for (size_t i = 0; i < count; ++i)
    {
      lo = std::min(lo, raw[i]);
      hi = std::max(hi, raw[i]);
    }
    const uint16_t range = (hi > lo) ? (hi - lo) : 1;

    QImage img(width, height, QImage::Format_Grayscale8);
    for (uint32_t y = 0; y < height; ++y)
    {
      uchar *row = img.scanLine(y);
      for (uint32_t x = 0; x < width; ++x)
        row[x] = static_cast<uchar>(255 * (raw[y * width + x] - lo) / range);
    }
    this->provider->SetFrame(img);
    ++this->frameId;
    emit this->FrameIdChanged();
    return;
  }
}

GZ_ADD_PLUGIN(ninjapilot::CameraView, gz::gui::Plugin)
