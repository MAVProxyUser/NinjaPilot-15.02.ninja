#include "GpsNoise.hh"

#include <gz/msgs/vector3d.pb.h>
#include <gz/plugin/Register.hh>

namespace ninjapilot
{
GpsNoise::GpsNoise() = default;

void GpsNoise::LoadConfig(const tinyxml2::XMLElement *_pluginElem)
{
  if (this->title.empty())
    this->title = "GPS noise";

  std::string topic = "/ninjapilot/gps_noise";
  if (_pluginElem)
  {
    if (auto elem = _pluginElem->FirstChildElement("topic"))
      if (elem->GetText())
        topic = elem->GetText();
  }
  this->pub = this->node.Advertise<gz::msgs::Vector3d>(topic);
  this->Publish();
}

double GpsNoise::PosNoise() const { return this->posNoise; }
double GpsNoise::VelNoise() const { return this->velNoise; }

void GpsNoise::SetPosNoise(double _m)
{
  this->posNoise = _m;
  this->PosNoiseChanged();
  this->Publish();
}

void GpsNoise::SetVelNoise(double _mps)
{
  this->velNoise = _mps;
  this->VelNoiseChanged();
  this->Publish();
}

void GpsNoise::Publish()
{
  if (!this->pub)
    return;
  // x = position sigma (m), y = velocity sigma (m/s). z unused.
  gz::msgs::Vector3d msg;
  msg.set_x(this->posNoise);
  msg.set_y(this->velNoise);
  msg.set_z(0.0);
  this->pub.Publish(msg);
}
}

GZ_ADD_PLUGIN(ninjapilot::GpsNoise, gz::gui::Plugin)
