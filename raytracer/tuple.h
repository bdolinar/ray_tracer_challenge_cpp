#pragma once

/// A tuple of 4 doubles (x, y, z, w).
struct Tuple
{
  /// Constructs tuple with coordinate values of 0.0.
  Tuple()
  : x()
  , y()
  , z()
  , w()
  {
  }

  /// Constructs tuple with given values.
  /// \param aX The X value.
  /// \param aY The Y value.
  /// \param aZ The Z value.
  /// \param aW The W value.
  Tuple(double aX, double aY, double aZ, double aW)
  : x(aX)
  , y(aY)
  , z(aZ)
  , w(aW)
  {
  }

  /// Equals operator.
  /// \param rhs The Tuple to check for equality.
  /// \return True if the Tuples are equal.
  bool operator==(const Tuple& rhs) const;

  /// Not equal operator.
  /// \param rhs The Tuple to check for equality.
  /// \return True if the Tuples are not equal.
  bool operator!=(const Tuple& rhs) const;

  /// Determine if tuple is a point.
  /// \return True if tuple is a point (w == 1.0).
  bool IsPoint() const;

  /// Determine if tuple is a vector.
  /// \return True if tuple is a vector (w == 0.0).
  bool IsVector() const;

  /// Get normal vector.
  /// \return Tuple in the same direction with unit length.
  Tuple Normalize() const;

  /// Calculate the magnitude (length).
  /// \return The magnitude or length of a vector tuple.
  double Magnitude() const;

  double x; ///< The X coordinate.
  double y; ///< The Y coordinate.
  double z; ///< The Z coordinate.
  double w; ///< The W coordinate.
};

/// Adds two tuples.
/// \param a The first operand.
/// \param b The second operand.
/// \return The result of adding the two tuples.
inline Tuple operator+(const Tuple& a, const Tuple& b)
{
  return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

/// Subtracts one tuple from another.
/// \param a The first operand.
/// \param b The second operand.
/// \return The result of subtracting the two tuples.
inline Tuple operator-(const Tuple& a, const Tuple& b)
{
  return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

/// Multiplies a tuple by a scalar.
/// \param a The tuple operand.
/// \param b The scalar operand.
/// \return The result of multiplying a tuple by a scalar.
inline Tuple operator*(const Tuple& a, double b)
{
  return {a.x * b, a.y * b, a.z * b, a.w * b};
}

/// Divides a tuple by a scalar.
/// \param a The tuple operand.
/// \param b The scalar operand.
/// \return The result of multiplying a tuple by a scalar.
inline Tuple operator/(const Tuple& a, double b)
{
  return {a.x / b, a.y / b, a.z / b, a.w / b};
}

/// Negates a tuple.
/// \param a The tuple to negate.
/// \return The negated tuple.
inline Tuple operator-(const Tuple& a)
{
  return {-a.x, -a.y, -a.z, -a.w};
}

/// Construct a point tuple.
/// \param x The X value.
/// \param y The Y value.
/// \param z The Z value.
inline Tuple Point(double x, double y, double z)
{
  Tuple p(x, y, z, 1.0);
  return p;
}

/// Construct a vector tuple.
/// \param x The X value.
/// \param y The Y value.
/// \param z The Z value.
inline Tuple Vector(double x, double y, double z)
{
  Tuple v(x, y, z, 0.0);
  return v;
}

/// Calculate the dot product of two vector tuples.
/// \param a The tuple operand.
/// \param b The scalar operand.
/// \return The dot product of the two vectors.
double Dot(const Tuple& a, const Tuple& b);

/// Calculate the cross product of two vector tuples.
/// \param a The tuple operand.
/// \param b The scalar operand.
/// \return The cross product of the two vectors.
Tuple Cross(const Tuple& a, const Tuple& b);

/// Calculate the reflection of an incoming vector off of a surface.
/// \param inVector The incoming vector to reflect off of surface.
/// \param normal The normal vector of the surface.
/// \return The reflection vector.
Tuple Reflect(const Tuple& inVector, const Tuple& normal);

/// Determine if two tuples are approximately equal (within 4 digits).
/// \param a The first tuple.
/// \param b The second tuple.
bool ApproximatelyEqual(const Tuple& a, const Tuple& b);

/// Determine if two tuples are nearly equal (within 10 digits).
/// \param a The first tuple.
/// \param b The second tuple.
bool NearlyEqual(const Tuple& a, const Tuple& b);
