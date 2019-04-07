#include <raytracer/light.h>

#include <memory>


//------------------------------------------------------------------------------
std::shared_ptr<Light>
Light::new_ptr(const Tuple& a_position, const Color& a_intensity)
{
  return std::make_shared<Light>(a_position, a_intensity);
}

//------------------------------------------------------------------------------
Light::Light(const Tuple& a_position, const Color& a_intensity)
    : position_(a_position)
      , intensity_(a_intensity)
{
}

//------------------------------------------------------------------------------
const Tuple& Light::position() const
{
  return position_;
}

//------------------------------------------------------------------------------
const Color& Light::intensity() const
{
  return intensity_;
}
