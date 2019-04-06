#include <raytracer/test_utils.h>

#include <cmath>
#include <algorithm>


bool ApproximatelyEqual(double a, double b)
{
  bool equal = EqualToDigits(a, b, 3);
  return equal;
}


bool NearlyEqual(double a, double b)
{
  bool equal = EqualToDigits(a, b, 10);
  return equal;
}

bool EqualToDigits(double a, double b, int digits)
{
  if (a == 0.0)
    return fabs(b) < pow(0.1, digits);
  else if (b == 0.0)
    return fabs(a) < pow(0.1, digits);

  double positiveDiff = fabs(a - b);
  double positiveMax = pow(0.1, digits) * std::max(fabs(a), fabs(b));
  return positiveDiff <= positiveMax;
}