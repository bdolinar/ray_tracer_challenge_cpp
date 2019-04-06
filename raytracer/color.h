#pragma once

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
  Color(double red, double green, double blue)
  : red_(red)
  , green_(green)
  , blue_(blue)
  {
  }

  /// Get the red component of the color.
  double Red() const { return red_; }

  /// Get the green component of the color.
  double Green() const { return green_; }

  /// Get the blue component of the color.
  double Blue() const { return blue_; }

  /// Determine if two colors are equal.
  bool operator==(const Color& rhs) const;

private:
  double red_;   ///< Red component from 0.0 to 1.0
  double green_; ///< Green component from 0.0 to 1.0
  double blue_;  ///< Blue component from 0.0 to 1.0
};

/// \brief Color addition operator.
/// \param[in] a The first operand.
/// \param[in] b The second operand.
/// \return The result of adding the two colors.
inline Color operator+(const Color& a, const Color& b)
{
  return Color(a.Red() + b.Red(), a.Green() + b.Green(), a.Blue() + b.Blue());
}

/// \brief Color subtraction operator.
/// \param[in] a The first operand.
/// \param[in] b The second operand.
/// \return The resulting of subtracting the two colors.
inline Color operator-(const Color& a, const Color& b)
{
  return Color(a.Red() - b.Red(), a.Green() - b.Green(), a.Blue() - b.Blue());
}

/// \brief Color multiplication operator.
/// \param[in] a The first operand.
/// \param[in] b The second operand.
/// \return The result of multiplying the two colors.
inline Color operator*(const Color& a, const Color& b)
{
  return Color(a.Red() * b.Red(), a.Green() * b.Green(), a.Blue() * b.Blue());
}

/// \brief Color and scalar mulitplication operator.
/// \param[in] a The first operand.
/// \param[in] b The second operand.
/// \return The result of muliplying a color by a scalar.
inline Color operator*(const Color& a, double b)
{
  return Color(a.Red() * b, a.Green() * b, a.Blue() * b);
}

/// \brief Color division operator.
/// \param[in] a The first operand.
/// \param[in] b The second operand.
/// \return The result of dividing the two colors.
inline Color operator/(const Color& a, double b)
{
  return Color(a.Red() / b, a.Green() / b, a.Blue() / b);
}

/// \brief Determine if two colors are approximately equal.
/// \param[in] a The first color.
/// \param[in] b The second color.
bool ApproximatelyEqual(const Color &a, const Color &b);
