#include <raytracer/color.h>

#include <algorithm>
#include <cmath>
#include "color.h"


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
  bool equal = red_ == rhs.red_ && green_ == rhs.green_ && blue_ == rhs.blue_;
  return equal;
}


Color color(double red, double green, double blue)
{
  return {red, green, blue};
}


bool ApproximatelyEqual(const Color& a, const Color& b)
{
  bool equalRed = EqualToDigits(a.Red(), b.Red(), 4);
  bool equalGreen = EqualToDigits(a.Green(), b.Green(), 4);
  bool equalBlue = EqualToDigits(a.Blue(), b.Blue(), 4);
  return equalRed && equalGreen && equalBlue;
}


bool NearlyEqual(const Color& a, const Color& b)
{
  bool equalRed = EqualToDigits(a.Red(), b.Red(), 10);
  bool equalGreen = EqualToDigits(a.Green(), b.Green(), 10);
  bool equalBlue = EqualToDigits(a.Blue(), b.Blue(), 10);
  return equalRed && equalGreen && equalBlue;
}
