
#pragma once

#include <raytracer/tuple.h>


class Matrix;

/// A light ray.
class Ray
{
public:
  /// Construct a ray.
  /// \param a_origin The point the ray begins at.
  /// \param a_direction The direction of the ray.
  Ray(const Tuple& a_origin, const Tuple& a_direction)
      : origin_(a_origin)
        , direction_(a_direction)
  {
  }

  /// Get the origin of the ray.
  /// \return The origin of the ray.
  const Tuple& origin() const
  {
    return origin_;
  }

  /// Get the direction of the ray.
  /// \return The direction of the ray.
  const Tuple& direction() const
  {
    return direction_;
  }

  /// Get a point a distance t from the ray origin.
  /// \param a_t The distance from the ray origin.
  /// \return The point at distance t from the ray origin.
  Tuple position(double a_t) const;

  /// Transform the ray by the given transformation matrix.
  /// \param a_transform The transformation matrix.
  /// \return The transformed ray.
  Ray transform(const Matrix& a_transform) const;

private:
  Tuple origin_;    ///< The origin of the ray.
  Tuple direction_; ///< The direction of the ray.
};
