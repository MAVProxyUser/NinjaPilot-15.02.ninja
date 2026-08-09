/*
 * WindControl - a Gazebo GUI panel with two sliders: wind speed (mph) and
 * the direction the wind blows FROM (compass degrees).
 *
 * Exists because the stock "Publisher" panel asks the user to hand-write a
 * protobuf message, which means doing the ENU conversion in your head every
 * time you want to change the wind. This does that conversion:
 *
 *     linear_velocity is the vector the wind blows TOWARD, so for a wind
 *     FROM bearing B at speed v:  x(east) = -v*sin(B), y(north) = -v*cos(B)
 */
#ifndef NINJAPILOT_WINDCONTROL_HH_
#define NINJAPILOT_WINDCONTROL_HH_

#include <gz/gui/Plugin.hh>
#include <gz/transport/Node.hh>

namespace ninjapilot
{
class WindControl : public gz::gui::Plugin
{
  Q_OBJECT

  /// Wind speed in mph, as shown on the slider.
  Q_PROPERTY(double windSpeed READ WindSpeed WRITE SetWindSpeed NOTIFY WindSpeedChanged)

  /// Direction the wind comes FROM, degrees clockwise from north.
  Q_PROPERTY(double windDir READ WindDir WRITE SetWindDir NOTIFY WindDirChanged)

  /// Compass label ("NW", "SSE", ...) for the current direction.
  Q_PROPERTY(QString compass READ Compass NOTIFY WindDirChanged)

  public: WindControl();
  public: ~WindControl() override = default;
  public: void LoadConfig(const tinyxml2::XMLElement *_pluginElem) override;

  public: double WindSpeed() const;
  public: void SetWindSpeed(double _mph);
  public: double WindDir() const;
  public: void SetWindDir(double _deg);
  public: QString Compass() const;

  signals: void WindSpeedChanged();
  signals: void WindDirChanged();

  private: void Publish();

  private: gz::transport::Node node;
  private: gz::transport::Node::Publisher pub;
  private: double windSpeed{0.0};
  private: double windDir{0.0};
};
}
#endif
