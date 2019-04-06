#pragma once

#include <memory>
#include <vector>

#include <raytracer/light.h>

class Intersection;
class Light;
class Ray;
class Sphere;

class World
{
public:
  /// \brief Get the number of objects in the World.
  /// \return The number of objects.
  int ObjectCount() const;

  /// \brief Add an object to the world.
  /// \param object The object to add to the world.
  void AddObject(std::shared_ptr<Sphere> object);

  /// \brief Add a light to the world.
  /// \param light The light to add to the world.
  void AddLight(std::shared_ptr<::Light> light);

  /// \brief Get the intersections of a ray with the world.
  /// \param ray The ray to intersect with the world.
  /// \return A list of intersections ordered in increasing T value.
  std::vector<Intersection> Intersect(const Ray& ray) const;

private:
  std::vector<std::shared_ptr<Sphere>> objects_; ///< The worlds objects.
  std::shared_ptr<::Light> light_;               ///< The worlds light.
};

/// \brief Get the default world which contains two spheres and a light.
/// \return A reference to the default world.
World& DefaultWorld();
