
#pragma once

#include <raytracer/tuple.h>

class Matrix;

class Ray
{
public:
  /// \brief Construct a ray.
  /// \param[in] origin The point the ray begins at.
  /// \param[in] direction The direction of the ray.
  Ray(const Tuple& origin, const Tuple& direction)
  : origin_(origin)
  , direction_(direction)
  {
  }

  /// \brief Get the origin of the ray.
  /// \return The origin of the ray.
  const Tuple& Origin() const { return origin_; }

  /// \brief Get the direction of the ray.
  /// \return The direction of the ray.
  const Tuple& Direction() const { return direction_; }

  /// \brief Get a point a distance t from the ray origin.
  /// \param[in] t The distance from the ray origin.
  /// \return The point at distance t from the ray origin.
  Tuple Position(double t) const;

  /// \brief Transform the ray by the given transformation matrix.
  /// \param[in] m The transformation matrix.
  /// \return The transformed ray.
  Ray Transform(const Matrix& m) const;

private:
  Tuple origin_;    ///< The origin of the ray.
  Tuple direction_; ///< The direction of the ray.
};
