#include <raytracer/ray.h>

#include <raytracer/matrix.h>


//------------------------------------------------------------------------------
Tuple Ray::position(double a_t) const
{
  return origin() + direction() * a_t;
}

//------------------------------------------------------------------------------
Ray Ray::transform(const Matrix& a_transform) const
{
  Ray r = {a_transform * origin(), a_transform * direction()};
  return r;
}
