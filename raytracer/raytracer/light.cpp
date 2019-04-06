#include "light.h"


Light::Light(const Tuple& position, const Color& intensity)
: position_(position)
, intensity_(intensity)
{
}


const Tuple& Light::Position() const
{
  return position_;
}


const Color& Light::Intensity() const
{
  return intensity_;
}
