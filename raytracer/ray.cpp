#include <raytracer/ray.h>

#include <raytracer/matrix.h>


Tuple Ray::Position(double t) const
{
  return Origin() + Direction() * t;
}


Ray Ray::Transform(const Matrix& m) const
{
  Ray r = {m * Origin(), m * Direction()};
  return r;
}
