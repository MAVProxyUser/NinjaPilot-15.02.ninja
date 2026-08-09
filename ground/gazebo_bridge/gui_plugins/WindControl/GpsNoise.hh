/*
 * GpsNoise - two sliders injecting GPS sensor noise, so the estimator can
 * be tested against a degraded fix instead of the perfect one Gazebo hands
 * out.
 *
 * The noise cannot be applied here: the GPS the flight controller sees is
 * synthesised by the bridge from Gazebo truth. This panel only publishes
 * the requested standard deviations; gazebo_bridge.py subscribes and adds
 * the noise as it builds GPSPositionSensor / GPSVelocitySensor.
 */
#ifndef NINJAPILOT_GPSNOISE_HH_
#define NINJAPILOT_GPSNOISE_HH_

#include <gz/gui/Plugin.hh>
#include <gz/transport/Node.hh>

namespace ninjapilot
{
class GpsNoise : public gz::gui::Plugin
{
  Q_OBJECT
  /// 1-sigma horizontal position noise, metres.
  Q_PROPERTY(double posNoise READ PosNoise WRITE SetPosNoise NOTIFY PosNoiseChanged)
  /// 1-sigma velocity noise, m/s.
  Q_PROPERTY(double velNoise READ VelNoise WRITE SetVelNoise NOTIFY VelNoiseChanged)

  public: GpsNoise();
  public: ~GpsNoise() override = default;
  public: void LoadConfig(const tinyxml2::XMLElement *_pluginElem) override;

  public: double PosNoise() const;
  public: void SetPosNoise(double _m);
  public: double VelNoise() const;
  public: void SetVelNoise(double _mps);

  signals: void PosNoiseChanged();
  signals: void VelNoiseChanged();

  private: void Publish();

  private: gz::transport::Node node;
  private: gz::transport::Node::Publisher pub;
  private: double posNoise{0.0};
  private: double velNoise{0.0};
};
}
#endif
