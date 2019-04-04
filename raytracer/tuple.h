#pragma once

struct Tuple
{
  /// \brief Constructs tuple with coordinate values of 0.0.
  Tuple()
  : x()
  , y()
  , z()
  , w()
  {
  }

  /// \brief Constructs tuple with given values.
  /// \param[in] aX The X value.
  /// \param[in] aY The Y value.
  /// \param[in] aZ The Z value.
  /// \param[in] aW The W value.
  Tuple(double aX, double aY, double aZ, double aW)
  : x(aX)
  , y(aY)
  , z(aZ)
  , w(aW)
  {
  }

  /// \brief Equals operator.
  /// \param rhs The Tuple to check for equality.
  /// \return True if the Tuples are equal.
  bool operator==(const Tuple& rhs) const;

  /// \brief Not equal operator.
  /// \param rhs The Tuple to check for equality.
  /// \return True if the Tuples are not equal.
  bool operator!=(const Tuple& rhs) const;

  /// \brief Determine if tuple is a point.
  /// \return True if tuple is a point (w == 1.0).
  bool IsPoint() const;

  /// \brief Determine if tuple is a vector.
  /// \return True if tuple is a vector (w == 0.0).
  bool IsVector() const;

  /// \brief Get normal vector.
  /// \return Tuple in the same direction with unit length.
  Tuple Normalize() const;

  /// \brief Calculate the magnitude (length).
  /// \return The magnitude or length of a vector tuple.
  double Magnitude() const;

  double x; ///< The X coordinate.
  double y; ///< The Y coordinate.
  double z; ///< The Z coordinate.
  double w; ///< The W coordinate.
};

/// \brief Adds two tuples.
/// \param[in] a The first operand.
/// \param[in] b The second operand.
/// \return The result of adding the two tuples.
inline Tuple operator+(const Tuple& a, const Tuple& b)
{
  return {a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w};
}

/// \brief Subtracts one tuple from another.
/// \param[in] a The first operand.
/// \param[in] b The second operand.
/// \return The result of subtracting the two tuples.
inline Tuple operator-(const Tuple& a, const Tuple& b)
{
  return {a.x - b.x, a.y - b.y, a.z - b.z, a.w - b.w};
}

/// \brief Multiplies a tuple by a scalar.
/// \param[in] a The tuple operand.
/// \param[in] b The scalar operand.
/// \return The result of multiplying a tuple by a scalar.
inline Tuple operator*(const Tuple& a, double b)
{
  return {a.x * b, a.y * b, a.z * b, a.w * b};
}

/// \brief Divides a tuple by a scalar.
/// \param[in] a The tuple operand.
/// \param[in] b The scalar operand.
/// \return The result of multiplying a tuple by a scalar.
inline Tuple operator/(const Tuple& a, double b)
{
  return {a.x / b, a.y / b, a.z / b, a.w / b};
}

/// \brief Negates a tuple.
/// \param[in] a The tuple to negate.
/// \return The negated tuple.
inline Tuple operator-(const Tuple& a)
{
  return {-a.x, -a.y, -a.z, -a.w};
}

/// \brief Construct a point tuple.
/// \param[in] x The X value.
/// \param[in] y The Y value.
/// \param[in] z The Z value.
inline Tuple Point(double x, double y, double z)
{
  Tuple p(x, y, z, 1.0);
  return p;
}

/// \brief Construct a vector tuple.
/// \param[in] x The X value.
/// \param[in] y The Y value.
/// \param[in] z The Z value.
inline Tuple Vector(double x, double y, double z)
{
  Tuple v(x, y, z, 0.0);
  return v;
}

/// \brief Calculate the dot product of two vector tuples.
/// \param[in] a The tuple operand.
/// \param[in] b The scalar operand.
/// \return The dot product of the two vectors.
double Dot(const Tuple& a, const Tuple& b);

/// \brief Calculate the cross product of two vector tuples.
/// \param[in] a The tuple operand.
/// \param[in] b The scalar operand.
/// \return The cross product of the two vectors.
Tuple Cross(const Tuple& a, const Tuple& b);

/// \brief Calculate the reflection of an incoming vector off of a surface.
/// \param[in] inVector The incoming vector to reflect off of surface.
/// \param[in] normal The normal vector of the surface.
/// \return The reflection vector.
Tuple Reflect(const Tuple& inVector, const Tuple& normal);

/// \brief Determine if two tuples are approximately equal (within 4 digits).
/// \param[in] a The first tuple.
/// \param[in] b The second tuple.
bool ApproximatelyEqual(const Tuple& a, const Tuple& b);

/// \brief Determine if two tuples are nearly equal (within 10 digits).
/// \param[in] a The first tuple.
/// \param[in] b The second tuple.
bool NearlyEqual(const Tuple& a, const Tuple& b);

/// \brief Determine if two doubles are approximately equal.
/// \param[in] a The first double.
/// \param[in] b The second double.
bool ApproximatelyEqual(double a, double b);

/// \brief Determine if two doubles are nearly equal.
/// \param[in] a The first double.
/// \param[in] b The second double.
bool NearlyEqual(double a, double b);

/// \brief Determine if two doubles are equal within a given number of digits.
/// \param[in] a The first double.
/// \param[in] b The second double.
bool EqualToDigits(double a, double b, int digits);
