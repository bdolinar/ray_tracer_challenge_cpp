#pragma once

#include <vector>

#include <raytracer/ray.h>
#include <raytracer/sphere.h>

class Computations;
class Sphere;

/// Data for an object and ray intersection.
class Intersection
{
public:

  /// \brief Construct an intersection.
  /// \param t The distance to the intersection.
  /// \param object The object at the intersection.
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
  /// \param rhs The intersection to compare against.
  /// \return True if the intersections are equal.
  bool operator==(const Intersection& rhs) const { return t_ == rhs.t_ && object_ == rhs.object_; }

  /// \brief Prepare data structure storing computations for an object intersection.
  /// \param ray The ray the object was intersected with.
  /// \return The computations data structure.
  Computations PrepareComputations(const Ray& ray) const;

private:
  double t_;             ///< The distance to the intersection.
  const Sphere* object_; ///< The intersected object.
};

typedef std::vector<Intersection> Intersections;

/// \brief Store computations for ray intersection.
struct Computations
{
  double t = 0.0;                 ///< T value along ray.
  const Sphere* object = nullptr; ///< Intersected object.
  Tuple point;                    ///< Point of intersection.
  Tuple toEye;                    ///< Vector directed to eye.
  Tuple normal;                   ///< Normal vector on object surface.
  bool inside = false;            ///< Did the ray come from inside the object?
};

/// \brief find the first intersection in the positive direction.
/// \param intersections A vector of intersections.
/// \return The first intersection found at a positive distance.
const Intersection* Hit(const Intersections& intersections);
