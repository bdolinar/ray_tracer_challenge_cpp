#pragma once

#include <math.h>
#include <vector>

#include "matrix.h"
#include "tuple.h"

class Intersection;
class Ray;

class Sphere
{
public:
  /// \brief Construct a unit sphere at the origin
  Sphere();

  /// \brief Get the transformation matrix of the sphere.
  /// \return The transformation matrix of the sphere.
  Matrix Transform() const;

  /// \brief Set the transformation matrix of the sphere.
  /// \param[in] t The new transformation matrix of the sphere.
  void Transform(const Matrix& t);

  /// \brief Determine if two spheres are the same object.
  /// \param[in] rhs The sphere to compare against.
  /// \return True if the two spheres are the same object.
  bool operator==(const Sphere& rhs) const { return this == &rhs; }

  /// \brief Get the intersections (if any) of the ray and this sphere.
  /// \param[in] ray The ray to intersect with the sphere.
  /// \return The intersections of the ray with this sphere.
  std::vector<Intersection> Intersect(const Ray& ray);

private:
  Matrix transform_; ///< Transformation matrix for sphere coordinates.
};
