#pragma once

#include <cmath>
#include <vector>

#include <raytracer/material.h>
#include <raytracer/matrix.h>
#include <raytracer/tuple.h>
#include "world.h"


class Intersection;
class Ray;

class Sphere
{
public:
  /// \brief Construct a Sphere shared pointer.
  /// \return The Sphere shared pointer.
  static std::shared_ptr<Sphere> New();

  /// \brief Construct a unit sphere at the origin
  Sphere();

  /// \brief Get the transformation matrix of the sphere.
  /// \return The transformation matrix of the sphere.
  Matrix Transform() const;

  /// \brief Set the transformation matrix of the sphere.
  /// \param[in] t The new transformation matrix of the sphere.
  void Transform(const Matrix& t);

  /// \brief Get the material of the sphere.
  /// \return The material of the sphere.
  Material Material() const;

  /// \brief Set the material of the sphere.
  /// \param[in] m The new material of the sphere.
  void Material(const class Material& m);

  /// \brief Determine if two spheres are the same object.
  /// \param[in] rhs The sphere to compare against.
  /// \return True if the two spheres are the same object.
  bool operator==(const Sphere& rhs) const { return this == &rhs; }

  /// \brief Get the intersections (if any) of the ray and this sphere.
  /// \param[in] ray The ray to intersect with the sphere.
  /// \return The intersections of the ray with this sphere.
  std::vector<Intersection> Intersect(const Ray& ray) const;

  /// \brief Get the normal given a point on the surface.
  /// \param[in] worldPoint The world space point on the sphere surface
  /// \return The normal vector at the surface of the sphere.
  Tuple NormalAt(Tuple worldPoint) const;

private:
  Matrix transform_;        ///< Transformation matrix for sphere coordinates.
  class Material material_; ///< The material of the sphere.
};
