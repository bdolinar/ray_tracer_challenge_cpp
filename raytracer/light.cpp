#include <raytracer/light.h>

#include <memory>


std::shared_ptr<Light> Light::New(const Tuple& position, const Color& intensity)
{
  return std::make_shared<Light>(position, intensity);
}


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
