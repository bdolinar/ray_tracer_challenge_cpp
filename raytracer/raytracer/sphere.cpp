#include "sphere.h"

#include "intersection.h"
#include "matrix.h"
#include "ray.h"


Sphere::Sphere()
: transform_(Matrix::IdentityMatrix(4))
{
}


Matrix Sphere::Transform() const
{
  return transform_;
}


void Sphere::Transform(const Matrix& t)
{
  transform_ = t;
}


Material Sphere::Material() const
{
  return material_;
}


void Sphere::Material(const class Material& m)
{
  material_ = m;
}


Intersections Sphere::Intersect(const Ray& ray)
{
  // use a ray translated to sphere coordinates to intersect
  Ray raySphere = ray.Transform(Transform().Inverse());
  std::vector<Intersection> intersections;
  Tuple sphere_to_ray = raySphere.Origin() - Point(0, 0, 0);
  double a = Dot(raySphere.Direction(), raySphere.Direction());
  double b = 2 * Dot(raySphere.Direction(), sphere_to_ray);
  double c = Dot(sphere_to_ray, sphere_to_ray) - 1;
  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0)
    return intersections;

  double t1 = (-b - sqrt(discriminant)) / (2 * a);
  double t2 = (-b + sqrt(discriminant)) / (2 * a);
  if (t1 > t2)
    std::swap(t1, t2);
  intersections = {{t1, *this}, {t2, *this}};
  return intersections;
}


Tuple Sphere::NormalAt(Tuple worldPoint) const
{
  Tuple objectPoint = Transform().Inverse() * worldPoint;
  Tuple objectNormal = objectPoint - Point(0, 0, 0);
  Tuple worldNormal = Transform().Inverse().Transpose() * objectNormal;
  worldNormal.w = 0;
  return worldNormal.Normalize();
}
