#include "intersection.h"


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
