#pragma once

#include <vector>

#include <raytracer/ray.h>
#include <raytracer/sphere.h>


class Computations;

class Sphere;

const double EPSILON = 1.0e-5;

/// Data for an object and ray intersection.
class Intersection
{
public:

  /// Construct an intersection.
  /// \param a_t The distance to the intersection.
  /// \param a_object The object at the intersection.
  Intersection(double a_t, const Sphere& a_object)
      : t_(a_t)
        , object_(&a_object)
  {
  }

  /// Get the distance to the intersection.
  /// \return The distance to the intersection.
  double t() const
  {
    return t_;
  }

  /// Get the intersected object.
  /// \return The intersected object.
  const Sphere& object() const
  {
    return *object_;
  }

  /// Determine if two intersections are equal.
  /// \param a_rhs The intersection to compare against.
  /// \return True if the intersections are equal.
  bool operator==(const Intersection& a_rhs) const
  {
    return t_ == a_rhs.t_ && object_ == a_rhs.object_;
  }

  /// Prepare data structure storing computations for an object intersection.
  /// \param a_ray The ray the object was intersected with.
  /// \return The computations data structure.
  Computations prepare_computations(const Ray& a_ray) const;

private:
  double t_;             ///< The distance to the intersection.
  const Sphere* object_; ///< The intersected object.
};

typedef std::vector<Intersection> Intersections;

/// Store computations for ray intersection.
struct Computations
{
  double t = 0.0;                 ///< T value along ray.
  const Sphere* object = nullptr; ///< Intersected object.
  Tuple point;                    ///< Point of intersection.
  Tuple to_eye;                   ///< Vector directed to eye.
  Tuple normal;                   ///< Normal vector on object surface.
  bool inside = false;            ///< Did the ray come from inside the object?
  Tuple over_point;               ///< Above surface for rounding errors.
};

/// find the first intersection in the positive direction.
/// \param a_intersections A vector of intersections.
/// \return The first intersection found at a positive distance.
const Intersection* hit(const Intersections& a_intersections);
