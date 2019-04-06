#include <raytracer/world.h>

#include <raytracer/intersection.h>
#include <raytracer/material.h>
#include <raytracer/sphere.h>
#include <raytracer/transform.h>


int World::ObjectCount() const
{
  return static_cast<int>(objects_.size());
}


Sphere& World::Object(int objectIndex)
{
  return *objects_.at(objectIndex);
}


void World::AddObject(std::shared_ptr<Sphere> object)
{
  objects_.push_back(object);
}


void World::AddLight(std::shared_ptr<::Light> light)
{
  light_ = light;
}


std::vector<Intersection> World::Intersect(const Ray& ray) const
{
  std::vector<Intersection> intersections;
  std::vector<Intersection> objectIntersections;
  for (const auto& object : objects_)
  {
    objectIntersections = object->Intersect(ray);
    intersections.insert(intersections.end(), objectIntersections.begin(),
                         objectIntersections.end());
  }
  std::sort(intersections.begin(), intersections.end(),
            [](const Intersection& i1, const Intersection& i2) { return i1.T() < i2.T(); });
  return intersections;
}


Color World::ShadeHit(const Computations& computations) const
{
  return Lighting(computations.object->Material(), *light_,
    computations.point, computations.toEye, computations.normal);
}


Color World::ColorAt(const Ray& ray) const
{
  std::vector<Intersection> intersections = Intersect(ray);
  const Intersection* intersection = Hit(intersections);
  Color color;
  if (intersection)
  {
    Computations computations = intersection->PrepareComputations(ray);
    color = ShadeHit(computations);
  }

  return color;
}


World DefaultWorld()
{
  World world;
  auto light = Light::New(Point(-10, 10, -10), Color(1, 1, 1));
  world.AddLight(light);

  Material material;
  material.Color(Color(0.8, 1.0, 0.6));
  material.Diffuse(0.7);
  material.Specular(0.2);

  std::shared_ptr<Sphere> s1 = Sphere::New();
  s1->Material(material);
  world.AddObject(s1);

  std::shared_ptr<Sphere> s2 = Sphere::New();
  s2->Transform(Scaling(0.5, 0.5, 0.5));
  world.AddObject(s2);

  return world;
}
