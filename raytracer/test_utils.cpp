#include <raytracer/test_utils.h>

#include <cmath>
#include <algorithm>


//------------------------------------------------------------------------------
bool approximately_equal(double a_lhs, double a_rhs)
{
  bool equal = equal_to_digits(a_lhs, a_rhs, 3);
  return equal;
}

//------------------------------------------------------------------------------
bool nearly_equal(double a_lhs, double a_rhs)
{
  bool equal;
  equal = equal_to_digits(a_lhs, a_rhs, 10);
  return equal;
}

//------------------------------------------------------------------------------
bool equal_to_digits(double a_lhs, double a_rhs, int a_digits)
{
  if (a_lhs == 0.0)
    return fabs(a_rhs) < pow(0.1, a_digits);
  else if (a_rhs == 0.0)
    return fabs(a_lhs) < pow(0.1, a_digits);

  double positive_diff = fabs(a_lhs - a_rhs);
  double positive_max = pow(0.1, a_digits) * std::max(fabs(a_lhs), fabs(a_rhs));
  return positive_diff <= positive_max;
}
