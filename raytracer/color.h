#pragma once

/// A color tuple.
class Color
{
public:
  /// Construct a color with default value of black.
  Color()
      : red_()
        , green_()
        , blue_()
  {
  }

  /// Construct a color given color components.
  Color(double a_red, double a_green, double a_blue)
      : red_(a_red)
        , green_(a_green)
        , blue_(a_blue)
  {
  }

  /// Get the red component of the color.
  double red() const
  {
    return red_;
  }

  /// Get the green component of the color.
  double green() const
  {
    return green_;
  }

  /// Get the blue component of the color.
  double blue() const
  {
    return blue_;
  }

  /// Determine if two colors are equal.
  bool operator==(const Color& a_rhs) const;

private:
  double red_;   ///< Red component from 0.0 to 1.0
  double green_; ///< Green component from 0.0 to 1.0
  double blue_;  ///< Blue component from 0.0 to 1.0
};

/// Color addition operator.
/// \param a_lhs The first operand.
/// \param a_rhs The second operand.
/// \return The result of adding the two colors.
inline Color operator+(const Color& a_lhs, const Color& a_rhs)
{
  return {a_lhs.red() + a_rhs.red(), a_lhs.green() + a_rhs.green(),
          a_lhs.blue() + a_rhs.blue()};
}

/// Color subtraction operator.
/// \param a_lhs The first operand.
/// \param a_rhs The second operand.
/// \return The resulting of subtracting the two colors.
inline Color operator-(const Color& a_lhs, const Color& a_rhs)
{
  return {a_lhs.red() - a_rhs.red(), a_lhs.green() - a_rhs.green(),
          a_lhs.blue() - a_rhs.blue()};
}

/// Color multiplication operator.
/// \param a_lhs The first operand.
/// \param a_rhs The second operand.
/// \return The result of multiplying the two colors.
inline Color operator*(const Color& a_lhs, const Color& a_rhs)
{
  return {a_lhs.red() * a_rhs.red(), a_lhs.green() * a_rhs.green(),
          a_lhs.blue() * a_rhs.blue()};
}

/// Color and scalar multiplication operator.
/// \param a_lhs The first operand.
/// \param a_rhs The second operand.
/// \return The result of multiplying a color by a scalar.
inline Color operator*(const Color& a_lhs, double a_rhs)
{
  return {a_lhs.red() * a_rhs, a_lhs.green() * a_rhs, a_lhs.blue() * a_rhs};
}

/// Color division operator.
/// \param a_lhs The first operand.
/// \param a_b The second operand.
/// \return The result of dividing the two colors.
inline Color operator/(const Color& a_lhs, double a_rhs)
{
  return {a_lhs.red() / a_rhs, a_lhs.green() / a_rhs, a_lhs.blue() / a_rhs};
}

/// Determine if two colors are approximately equal (within 4 digits).
/// \param a_lhs The first color.
/// \param a_rhs The second color.
bool approximately_equal(const Color& a_lhs, const Color& a_rhs);

/// Determine if two colors are nearly equal (within 10 digits).
/// \param a_lhs The first color.
/// \param a_rhs The second color.
bool nearly_equal(const Color& a_lhs, const Color& a_rhs);
