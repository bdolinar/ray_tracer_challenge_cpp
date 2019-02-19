#include "color.h"

#include <algorithm>
#include <math.h>

namespace
{
bool EqualToDigits(double a, double b, int digits)
{
  double positiveDiff = fabs(a - b);
  double positiveMax = pow(0.1, digits) * std::max(fabs(a), fabs(b));
  return positiveDiff <= positiveMax;
}

} // namespace


bool Color::operator==(const Color& rhs) const
{
  bool equalRed = EqualToDigits(red_, rhs.red_, 10);
  bool equalGreen = EqualToDigits(green_, rhs.green_, 10);
  bool equalBlue = EqualToDigits(blue_, rhs.blue_, 10);
  return equalRed && equalGreen && equalBlue;
}


Color color(double red, double green, double blue)
{
  return Color(red, green, blue);
}
