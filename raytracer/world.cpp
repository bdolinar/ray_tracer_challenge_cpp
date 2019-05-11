#include <raytracer/world.h>

#include <algorithm>
#include <raytracer/intersection.h>
#include <raytracer/material.h>
#include <raytracer/sphere.h>
#include <raytracer/transform.h>


//------------------------------------------------------------------------------
int World::object_count() const
{
  return static_cast<int>(objects_.size());
}

//------------------------------------------------------------------------------
Sphere& World::object(int a_object_index)
{
  return *objects_.at(a_object_index);
}

//------------------------------------------------------------------------------
void World::add_object(std::unique_ptr<Sphere> a_object)
{
  objects_.push_back(std::move(a_object));
}

//------------------------------------------------------------------------------
void World::set_light(std::unique_ptr<::Light> a_light)
{
  light_ = std::move(a_light);
}

//------------------------------------------------------------------------------
std::vector<Intersection> World::intersect(const Ray& a_ray) const
{
  std::vector<Intersection> intersections;
  std::vector<Intersection> object_intersections;
  for (const auto& object : objects_)
  {
    object_intersections = object->intersect(a_ray);
    intersections.insert(intersections.end(), object_intersections.begin(),
                         object_intersections.end());
  }
  std::sort(intersections.begin(), intersections.end(),
            [](const Intersection& a_lhs, const Intersection& a_rhs)
            { return a_lhs.t() < a_rhs.t(); });
  return intersections;
}

//------------------------------------------------------------------------------
Color World::shade_hit(const Computations& a_computations) const
{
  bool shadowed = is_shadowed(a_computations.over_point);
  return lighting(a_computations.object->material(), *light_,
                  a_computations.point, a_computations.to_eye,
                  a_computations.normal, shadowed);
}

//------------------------------------------------------------------------------
Color World::color_at(const Ray& a_ray) const
{
  std::vector<Intersection> intersections = intersect(a_ray);
  const Intersection* intersection = hit(intersections);
  Color color;
  if (intersection)
  {
    Computations computations = intersection->prepare_computations(a_ray);
    color = shade_hit(computations);
  }

  return color;
}

bool World::is_shadowed(const Tuple& a_point) const
{
  Tuple to_light = light_->position() - a_point;
  double distance = to_light.magnitude();
  Tuple direction = to_light.normalize();
  Ray ray(a_point, direction);
  Intersections intersections = intersect(ray);
  const Intersection* intersection = hit(intersections);
  if (intersection && intersection->t() < distance)
    return true;
  return false;
}

//------------------------------------------------------------------------------
World default_world()
{
  World world;
  auto light = Light::new_ptr(point(-10, 10, -10), Color(1, 1, 1));
  world.set_light(std::move(light));

  Material material;
  material.set_color(Color(0.8, 1.0, 0.6));
  material.set_diffuse(0.7);
  material.set_specular(0.2);

  std::unique_ptr<Sphere> s1 = Sphere::new_ptr();
  s1->set_material(material);
  world.add_object(std::move(s1));

  std::unique_ptr<Sphere> s2 = Sphere::new_ptr();
  s2->set_transform(scaling(0.5, 0.5, 0.5));
  world.add_object(std::move(s2));

  return world;
}
