#include <raytracer/color.h>

#include <algorithm>
#include <cmath>
#include <raytracer/color.h>
#include <raytracer/test_utils.h>


namespace
{
} // namespace


//------------------------------------------------------------------------------
bool Color::operator==(const Color& a_rhs) const
{
  bool equal =
      red_ == a_rhs.red_ && green_ == a_rhs.green_ && blue_ == a_rhs.blue_;
  return equal;
}

//------------------------------------------------------------------------------
Color color(double a_red, double a_green, double a_blue)
{
  return {a_red, a_green, a_blue};
}

//------------------------------------------------------------------------------
bool approximately_equal(const Color& a_lhs, const Color& a_rhs)
{
  bool equal_red = equal_to_digits(a_lhs.red(), a_rhs.red(), 4);
  bool equal_green = equal_to_digits(a_lhs.green(), a_rhs.green(), 4);
  bool equal_blue = equal_to_digits(a_lhs.blue(), a_rhs.blue(), 4);
  return equal_red && equal_green && equal_blue;
}

//------------------------------------------------------------------------------
bool nearly_equal(const Color& a_lhs, const Color& a_rhs)
{
  bool equal_red = equal_to_digits(a_lhs.red(), a_rhs.red(), 10);
  bool equal_green = equal_to_digits(a_lhs.green(), a_rhs.green(), 10);
  bool equal_blue = equal_to_digits(a_lhs.blue(), a_rhs.blue(), 10);
  return equal_red && equal_green && equal_blue;
}
