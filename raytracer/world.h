#pragma once

#include <memory>
#include <vector>

#include <raytracer/intersection.h>
#include <raytracer/light.h>


class Computations;

class Intersection;

class Light;

class Ray;

class Sphere;

/// World for a ray traced scene.
class World
{
public:
  /// Get the number of objects in the World.
  /// \return The number of objects.
  int object_count() const;

  /// Get object of given index in world.
  /// \param a_object_index The index of the object to get.
  /// \return The object at the given index.
  Sphere& object(int a_object_index);

  /// Add an object to the world.
  /// \param a_object The object to add to the world.
  void add_object(std::unique_ptr<Sphere> a_object);

  /// Set the world light.
  /// \param a_light The light to add to the world.
  void set_light(std::unique_ptr<::Light> a_light);

  /// Get the intersections of a ray with the world.
  /// \param a_ray The ray to intersect with the world.
  /// \return A list of intersections ordered in increasing T value.
  std::vector<Intersection> intersect(const Ray& a_ray) const;

  /// Calculate the color at a hit given calculations.
  /// \param a_computations The calculations at the hit object.
  /// \return The color at the ray trace hit.
  Color shade_hit(const Computations& a_computations) const;

  /// Calculate the color where a ray hits the world.
  /// \param a_ray The ray to cast into the world.
  /// \return  The color where the ray hits the world.
  Color color_at(const Ray& a_ray) const;

private:
  std::vector<std::unique_ptr<Sphere>> objects_; ///< The worlds objects.
  std::unique_ptr<::Light> light_;               ///< The worlds light.
};

/// Get the default world which contains two spheres and a light.
/// \return A reference to the default world.
World default_world();
