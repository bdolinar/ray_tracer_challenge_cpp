#pragma once

#include <memory>
#include <vector>

#include <raytracer/light.h>
#include "intersection.h"

class Computations;
class Intersection;
class Light;
class Ray;
class Sphere;

/// World for a raytraced scene.
class World
{
public:
  /// \brief Get the number of objects in the World.
  /// \return The number of objects.
  int ObjectCount() const;

  /// \brief Get object of given index in world.
  /// \param objectIndex The index of the object to get.
  /// \return The object at the given index.
  Sphere& Object(int objectIndex);

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

  /// \brief Calculate the color at a hit given calculations.
  /// \param computations The calculations at the hit object.
  /// \return The color at the ray trace hit.
  Color ShadeHit(const Computations& computations) const;

  /// \brief Calculate the color where a ray hits the world.
  /// \param ray The ray to cast into the world.
  /// \return  The color where the ray hits the world.
  Color ColorAt(const Ray& ray) const;

private:
  std::vector<std::shared_ptr<Sphere>> objects_; ///< The worlds objects.
  std::shared_ptr<::Light> light_;               ///< The worlds light.
};

/// \brief Get the default world which contains two spheres and a light.
/// \return A reference to the default world.
World DefaultWorld();
