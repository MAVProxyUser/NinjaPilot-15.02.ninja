/*
 * CameraView - a camera image panel with NO chrome.
 *
 * gz-gui ships ImageDisplay, which works, but it renders a permanent
 * "Subscribed to: <topic>" banner. That string is baked into
 * libImageDisplay.dylib's compiled QML resource and there is no config key
 * to hide it - topic_picker only swaps it for a topic combo box, which is
 * just different chrome. On a 300x225 panel the banner eats a third of the
 * view, and with three cameras stacked it is three useless toasts.
 *
 * So: subscribe to gz.msgs.Image, convert to a QImage, hand it to QML via a
 * QQuickImageProvider, and draw nothing else.
 */
#ifndef NINJAPILOT_CAMERAVIEW_HH_
#define NINJAPILOT_CAMERAVIEW_HH_

#include <gz/gui/Plugin.hh>
#include <gz/transport/Node.hh>
#include <gz/msgs/image.pb.h>

#include <QImage>
#include <QMutex>
#include <QQuickImageProvider>
#include <QString>

namespace ninjapilot
{
/// Serves the newest frame to QML under image://<provider>/frame.
class FrameProvider : public QQuickImageProvider
{
  public: FrameProvider() : QQuickImageProvider(QQuickImageProvider::Image) {}
  public: QImage requestImage(const QString &, QSize *_size,
                              const QSize &) override;
  public: void SetFrame(const QImage &_img);

  private: QImage frame;
  private: QMutex mutex;
};

class CameraView : public gz::gui::Plugin
{
  Q_OBJECT
  /// Bumped on every new frame; QML re-requests the image when it changes,
  /// because an image:// URL is cached and would otherwise never refresh.
  Q_PROPERTY(int frameId READ FrameId NOTIFY FrameIdChanged)

  public: CameraView();
  public: ~CameraView() override;
  public: void LoadConfig(const tinyxml2::XMLElement *_pluginElem) override;

  public: int FrameId() const;

  signals: void FrameIdChanged();

  private: void OnImage(const gz::msgs::Image &_msg);

  private: gz::transport::Node node;
  private: FrameProvider *provider{nullptr};
  private: QString providerName;
  private: int frameId{0};
};
}
#endif
