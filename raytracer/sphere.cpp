#include <raytracer/sphere.h>

#include <algorithm>

#include <raytracer/intersection.h>


//------------------------------------------------------------------------------
std::unique_ptr<Sphere> Sphere::new_ptr()
{
  return std::unique_ptr<Sphere>(new Sphere);
}


//------------------------------------------------------------------------------
Sphere::Sphere()
    : transform_(Matrix::identity_matrix(4))
{
}


//------------------------------------------------------------------------------
Matrix Sphere::transform() const
{
  return transform_;
}


//------------------------------------------------------------------------------
void Sphere::set_transform(const Matrix& a_transform)
{
  transform_ = a_transform;
}


//------------------------------------------------------------------------------
Material Sphere::material() const
{
  return material_;
}


//------------------------------------------------------------------------------
void Sphere::set_material(const class Material& a_material)
{
  material_ = a_material;
}


//------------------------------------------------------------------------------
Intersections Sphere::intersect(const Ray& a_ray) const
{
  // use a ray translated to sphere coordinates to intersect
  Ray ray_sphere = a_ray.transform(transform().inverse());
  std::vector<Intersection> intersections;
  Tuple sphere_to_ray = ray_sphere.origin() - point(0, 0, 0);
  double a = dot(ray_sphere.direction(), ray_sphere.direction());
  double b = 2 * dot(ray_sphere.direction(), sphere_to_ray);
  double c = dot(sphere_to_ray, sphere_to_ray) - 1;
  double discriminant = b * b - 4 * a * c;
  if (discriminant < 0)
    return intersections;

  double t_1 = (-b - sqrt(discriminant)) / (2 * a);
  double t_2 = (-b + sqrt(discriminant)) / (2 * a);
  if (t_1 > t_2)
    std::swap(t_1, t_2);
  intersections = {{t_1, *this},
                   {t_2, *this}};
  return intersections;
}


//------------------------------------------------------------------------------
Tuple Sphere::normal_at(Tuple a_world_point) const
{
  Tuple object_point = transform().inverse() * a_world_point;
  Tuple object_normal = object_point - point(0, 0, 0);
  Tuple world_normal = transform().inverse().transpose() * object_normal;
  world_normal.set_w(0);
  return world_normal.normalize();
}
