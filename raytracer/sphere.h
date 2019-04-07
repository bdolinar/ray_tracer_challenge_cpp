#pragma once

#include <cmath>
#include <vector>

#include <raytracer/material.h>
#include <raytracer/matrix.h>
#include <raytracer/tuple.h>
#include <raytracer/world.h>


class Intersection;

class Ray;

/// A sphere object.
class Sphere
{
public:
  /// Construct a Sphere shared pointer.
  /// \return The Sphere shared pointer.
  static std::shared_ptr<Sphere> new_ptr();

  /// Construct a unit sphere at the origin
  Sphere();

  /// Get the transformation matrix of the sphere.
  /// \return The transformation matrix of the sphere.
  Matrix transform() const;

  /// Set the transformation matrix of the sphere.
  /// \param a_transform The new transformation matrix of the sphere.
  void set_transform(const Matrix& a_transform);

  /// Get the material of the sphere.
  /// \return The material of the sphere.
  Material material() const;

  /// Set the material of the sphere.
  /// \param a_material The new material of the sphere.
  void set_material(const class Material& a_material);

  /// Determine if two spheres are the same object.
  /// \param a_rhs The sphere to compare against.
  /// \return True if the two spheres are the same object.
  bool operator==(const Sphere& a_rhs) const
  {
    return this == &a_rhs;
  }

  /// Get the intersections (if any) of the ray and this sphere.
  /// \param a_ray The ray to intersect with the sphere.
  /// \return The intersections of the ray with this sphere.
  std::vector<Intersection> intersect(const Ray& a_ray) const;

  /// Get the normal given a point on the surface.
  /// \param a_world_point The world space point on the sphere surface
  /// \return The normal vector at the surface of the sphere.
  Tuple normal_at(Tuple a_world_point) const;

private:
  Matrix transform_;        ///< Transformation matrix for sphere coordinates.
  class Material material_; ///< The material of the sphere.
};
