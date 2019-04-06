
#pragma once

#include <raytracer/tuple.h>

class Matrix;

/// A light ray.
class Ray
{
public:
  /// Construct a ray.
  /// \param origin The point the ray begins at.
  /// \param direction The direction of the ray.
  Ray(const Tuple& origin, const Tuple& direction)
  : origin_(origin)
  , direction_(direction)
  {
  }

  /// Get the origin of the ray.
  /// \return The origin of the ray.
  const Tuple& Origin() const { return origin_; }

  /// Get the direction of the ray.
  /// \return The direction of the ray.
  const Tuple& Direction() const { return direction_; }

  /// Get a point a distance t from the ray origin.
  /// \param t The distance from the ray origin.
  /// \return The point at distance t from the ray origin.
  Tuple Position(double t) const;

  /// Transform the ray by the given transformation matrix.
  /// \param m The transformation matrix.
  /// \return The transformed ray.
  Ray Transform(const Matrix& m) const;

private:
  Tuple origin_;    ///< The origin of the ray.
  Tuple direction_; ///< The direction of the ray.
};
