#pragma once

#include <vector>

#include <raytracer/ray.h>
#include <raytracer/sphere.h>

class Sphere;

class Intersection
{
public:
  /// \brief Construct an intersection.
  /// \param[in] t The distance to the intersection.
  /// \param[in] object The object at the intersection.
  Intersection(double t, const Sphere& object)
  : t_(t)
  , object_(&object)
  {
  }

  /// \brief Get the distance to the intersection.
  /// \return The distance to the intersection.
  double T() const { return t_; }

  /// \brief Get the intersected object.
  /// \return The intersected object.
  const Sphere& Object() const { return *object_; }

  /// \brief Determine if two intersections are equal.
  /// \param[in] rhs The intersection to compare against.
  /// \return True if the intersections are equal.
  bool operator==(const Intersection& rhs) const { return t_ == rhs.t_ && object_ == rhs.object_; }

private:
  double t_;             ///< The distance to the intersection.
  const Sphere* object_; ///< The intersected object.
};

typedef std::vector<Intersection> Intersections;

/// \brief find the first intersection in the positive direction.
/// \param[in] intersections A vector of intersections.
/// \return The first intersection found at a positive distance.
const Intersection* Hit(const Intersections& intersections);
