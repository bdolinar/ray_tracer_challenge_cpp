#include "color.h"

#include <algorithm>
#include <math.h>

namespace
{
static bool equal_to_digits(double a, double b, int digits)
{
  double positiveDiff = fabs(a - b);
  double positiveMax = pow(0.1, digits) * std::max(fabs(a), fabs(b));
  return positiveDiff <= positiveMax;
}

} // namespace

bool Color::operator==(const Color& rhs) const
{
  bool equalRed = equal_to_digits(red_, rhs.red_, 10);
  bool equalGreen = equal_to_digits(green_, rhs.green_, 10);
  bool equalBlue = equal_to_digits(blue_, rhs.blue_, 10);
  return equalRed && equalGreen && equalBlue;
}

Color color(double red, double green, double blue)
{
  return Color(red, green, blue);
}
