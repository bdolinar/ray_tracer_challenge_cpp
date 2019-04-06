#include <raytracer/intersection.h>


const Intersection* Hit(const Intersections& intersections)
{
  const Intersection* h = nullptr;
  for (auto& intersection : intersections)
  {
    if (intersection.T() > 0)
    {
      if (!h || intersection.T() < h->T())
      {
        h = &intersection;
      }
    }
  }

  return h;
}


Computations Intersection::PrepareComputations(const Ray& ray) const
{
  // instantiate a data structure for storing some precomputed values comps ← new computations data structure
  // copy the intersection's properties, for convenience
  double t = T();
  const Sphere* object = &Object();
  Tuple point = ray.Position(t);
  Tuple toEye = -ray.Direction();
  Tuple normal = object->NormalAt(point);
  bool inside = false;
  if (Dot(normal, toEye) < 0)
  {
    inside = true;
    normal = - normal;
  }
  else
  {
    inside = false;
  }
  return {t, object, point, toEye, normal, inside};
}
