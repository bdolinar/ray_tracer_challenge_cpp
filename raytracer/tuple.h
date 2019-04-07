#pragma once

/// A tuple of 4 doubles (x, y, z, w).
struct Tuple
{
  /// Constructs tuple with coordinate values of 0.0.
  Tuple()
      : x_()
        , y_()
        , z_()
        , w_()
  {
  }

  /// Constructs tuple with given values.
  /// \param a_x The X value.
  /// \param a_y The Y value.
  /// \param a_z The Z value.
  /// \param a_w The W value.
  Tuple(double a_x, double a_y, double a_z, double a_w)
      : x_(a_x)
        , y_(a_y)
        , z_(a_z)
        , w_(a_w)
  {
  }

  /// Get the X value.
  /// \return The X value.
  double x() const
  { return x_; }

  /// Get the Y value.
  /// \return The Y value.
  double y() const
  { return y_; }

  /// Get the Z value.
  /// \return The Z value.
  double z() const
  { return z_; }

  /// Get the W value.
  /// \return The W value.
  double w() const
  { return w_; }

  /// Set the W value.
  /// \param a_w The W value.
  void set_w(double a_w)
  { w_ = a_w; }

  /// Equals operator.
  /// \param a_rhs The Tuple to check for equality.
  /// \return True if the Tuples are equal.
  bool operator==(const Tuple& a_rhs) const;

  /// Not equal operator.
  /// \param a_rhs The Tuple to check for equality.
  /// \return True if the Tuples are not equal.
  bool operator!=(const Tuple& a_rhs) const;

  /// Determine if tuple is a point.
  /// \return True if tuple is a point (w == 1.0).
  bool is_point() const;

  /// Determine if tuple is a vector.
  /// \return True if tuple is a vector (w == 0.0).
  bool is_vector() const;

  /// Get normal vector.
  /// \return Tuple in the same direction with unit length.
  Tuple normalize() const;

  /// Calculate the magnitude (length).
  /// \return The magnitude or length of a vector tuple.
  double magnitude() const;

  double x_; ///< The X coordinate.
  double y_; ///< The Y coordinate.
  double z_; ///< The Z coordinate.
  double w_; ///< The W coordinate.
};

/// Adds two tuples.
/// \param a_lhs The first operand.
/// \param a_rhs The second operand.
/// \return The result of adding the two tuples.
inline Tuple operator+(const Tuple& a_lhs, const Tuple& a_rhs)
{
  return {a_lhs.x_ + a_rhs.x_, a_lhs.y_ + a_rhs.y_, a_lhs.z_ + a_rhs.z_,
          a_lhs.w_ + a_rhs.w_};
}

/// Subtracts one tuple from another.
/// \param a_lhs The first operand.
/// \param a_rhs The second operand.
/// \return The result of subtracting the two tuples.
inline Tuple operator-(const Tuple& a_lhs, const Tuple& a_rhs)
{
  return {a_lhs.x_ - a_rhs.x_, a_lhs.y_ - a_rhs.y_, a_lhs.z_ - a_rhs.z_,
          a_lhs.w_ - a_rhs.w_};
}

/// Multiplies a tuple by a scalar.
/// \param a_lhs The tuple operand.
/// \param a_rhs The scalar operand.
/// \return The result of multiplying a tuple by a scalar.
inline Tuple operator*(const Tuple& a_lhs, double a_rhs)
{
  return {a_lhs.x_ * a_rhs, a_lhs.y_ * a_rhs, a_lhs.z_ * a_rhs,
          a_lhs.w_ * a_rhs};
}

/// Divides a tuple by a scalar.
/// \param a_lhs The tuple operand.
/// \param a_rhs The scalar operand.
/// \return The result of multiplying a tuple by a scalar.
inline Tuple operator/(const Tuple& a_lhs, double a_rhs)
{
  return {a_lhs.x_ / a_rhs, a_lhs.y_ / a_rhs, a_lhs.z_ / a_rhs,
          a_lhs.w_ / a_rhs};
}

/// Negates a tuple.
/// \param a_rhs The tuple to negate.
/// \return The negated tuple.
inline Tuple operator-(const Tuple& a_rhs)
{
  return {-a_rhs.x_, -a_rhs.y_, -a_rhs.z_, -a_rhs.w_};
}

/// Construct a point tuple.
/// \param a_x The X value.
/// \param a_y The Y value.
/// \param a_z The Z value.
inline Tuple point(double a_x, double a_y, double a_z)
{
  Tuple p(a_x, a_y, a_z, 1.0);
  return p;
}

/// Construct a vector tuple.
/// \param a_x The X value.
/// \param a_y The Y value.
/// \param a_z The Z value.
inline Tuple vector(double a_x, double a_y, double a_z)
{
  Tuple v(a_x, a_y, a_z, 0.0);
  return v;
}

/// Calculate the dot product of two vector tuples.
/// \param a_lhs The tuple operand.
/// \param a_rhs The scalar operand.
/// \return The dot product of the two vectors.
double dot(const Tuple& a_lhs, const Tuple& a_rhs);

/// Calculate the cross product of two vector tuples.
/// \param a_lhs The tuple operand.
/// \param a_rhs The scalar operand.
/// \return The cross product of the two vectors.
Tuple cross(const Tuple& a_lhs, const Tuple& a_rhs);

/// Calculate the reflection of an incoming vector off of a surface.
/// \param a_in_vector The incoming vector to reflect off of surface.
/// \param a_normal The normal vector of the surface.
/// \return The reflection vector.
Tuple reflect(const Tuple& a_in_vector, const Tuple& a_normal);

/// Determine if two tuples are approximately equal (within 4 digits).
/// \param a_lhs The first tuple.
/// \param a_rhs The second tuple.
bool approximately_equal(const Tuple& a_lhs, const Tuple& a_rhs);

/// Determine if two tuples are nearly equal (within 10 digits).
/// \param a_lhs The first tuple.
/// \param a_rhs The second tuple.
bool nearly_equal(const Tuple& a_lhs, const Tuple& a_rhs);
