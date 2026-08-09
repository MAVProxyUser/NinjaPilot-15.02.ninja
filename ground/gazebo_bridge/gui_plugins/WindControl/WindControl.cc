#include "WindControl.hh"

#include <cmath>
#include <string>

#include <gz/msgs/wind.pb.h>
#include <gz/plugin/Register.hh>

namespace ninjapilot
{

namespace {
constexpr double kMphToMps = 0.44704;
const char *kCompass[16] = {"N", "NNE", "NE", "ENE", "E", "ESE", "SE", "SSE",
                            "S", "SSW", "SW", "WSW", "W", "WNW", "NW", "NNW"};
}

WindControl::WindControl() = default;

void WindControl::LoadConfig(const tinyxml2::XMLElement *_pluginElem)
{
  if (this->title.empty())
    this->title = "Wind";

  // Topic defaults to this world's wind topic but stays overridable from the
  // SDF, so the panel is not welded to one world name.
  std::string topic = "/world/quadcopter/wind";
  if (_pluginElem)
  {
    if (auto elem = _pluginElem->FirstChildElement("topic"))
      if (elem->GetText())
        topic = elem->GetText();
  }
  this->pub = this->node.Advertise<gz::msgs::Wind>(topic);
  this->Publish();
}

double WindControl::WindSpeed() const { return this->windSpeed; }
double WindControl::WindDir() const { return this->windDir; }

void WindControl::SetWindSpeed(double _mph)
{
  this->windSpeed = _mph;
  this->WindSpeedChanged();
  this->Publish();
}

void WindControl::SetWindDir(double _deg)
{
  this->windDir = _deg;
  this->WindDirChanged();
  this->Publish();
}

QString WindControl::Compass() const
{
  int idx = static_cast<int>(std::round(this->windDir / 22.5)) % 16;
  if (idx < 0)
    idx += 16;
  return QString::fromStdString(std::string(kCompass[idx]));
}

void WindControl::Publish()
{
  if (!this->pub)
    return;

  const double mps = this->windSpeed * kMphToMps;
  const double rad = this->windDir * M_PI / 180.0;

  gz::msgs::Wind msg;
  // Sliders state the direction the wind comes FROM; the message wants the
  // vector it blows TOWARD, in ENU (x east, y north).
  msg.mutable_linear_velocity()->set_x(-mps * std::sin(rad));
  msg.mutable_linear_velocity()->set_y(-mps * std::cos(rad));
  msg.mutable_linear_velocity()->set_z(0.0);
  // Without this the WindEffects system applies nothing at all.
  msg.set_enable_wind(mps > 0.01);
  this->pub.Publish(msg);
}
}

GZ_ADD_PLUGIN(ninjapilot::WindControl, gz::gui::Plugin)
