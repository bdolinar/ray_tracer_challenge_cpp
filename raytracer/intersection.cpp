#include <raytracer/intersection.h>


//------------------------------------------------------------------------------
const Intersection* hit(const Intersections& a_intersections)
{
  const Intersection* h = nullptr;
  for (auto& intersection : a_intersections)
  {
    if (intersection.t() > 0)
    {
      if (!h || intersection.t() < h->t())
      {
        h = &intersection;
      }
    }
  }

  return h;
}

//------------------------------------------------------------------------------
Computations Intersection::prepare_computations(const Ray& a_ray) const
{
  double t_value = t();
  const Sphere* object_value = &object();
  Tuple point = a_ray.position(t_value);
  Tuple to_eye = -a_ray.direction();
  Tuple normal = object_value->normal_at(point);

  bool inside;
  if (dot(normal, to_eye) < 0)
  {
    inside = true;
    normal = -normal;
  }
  else
  {
    inside = false;
  }
  Tuple over_point = point + normal * EPSILON;

  return {t_value, object_value, point, to_eye, normal, inside, over_point};
}
