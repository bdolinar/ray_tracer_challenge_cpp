#include "tuple.h"

#include <algorithm>
#include <math.h>


bool Tuple::operator==(const Tuple& rhs) const
{
  bool equalX = EqualToDigits(x, rhs.x, 10);
  bool equalY = EqualToDigits(y, rhs.y, 10);
  bool equalZ = EqualToDigits(z, rhs.z, 10);
  bool equalW = EqualToDigits(w, rhs.w, 10);
  return equalX && equalY && equalZ && equalW;
}


bool Tuple::IsPoint() const
{
  return w == 1.0;
}


bool Tuple::IsVector() const
{
  return w == 0.0;
}


double Tuple::Magnitude() const
{
  return sqrt(x * x + y * y + z * z + w * w);
}


Tuple Tuple::Normalize() const
{
  double mag = Magnitude();
  return Tuple(x / mag, y / mag, z / mag, w / mag);
}


double Dot(const Tuple& a, const Tuple& b)
{
  double result = a.x * b.x + a.y * b.y + a.z * b.z + a.w * b.w;
  return result;
}


Tuple Cross(const Tuple& a, const Tuple& b)
{
  return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}


Tuple Reflect(const Tuple& inVector, const Tuple& normal)
{
  return inVector - normal * 2 * Dot(inVector, normal);
}


bool ApproximatelyEqual(const Tuple& a, const Tuple& b)
{
  bool equalX = EqualToDigits(a.x, b.x, 4);
  bool equalY = EqualToDigits(a.y, b.y, 4);
  bool equalZ = EqualToDigits(a.z, b.z, 4);
  bool equalW = EqualToDigits(a.w, b.w, 4);
  return equalX && equalY && equalZ && equalW;
}


bool ApproximatelyEqual(double a, double b)
{
  bool equal = EqualToDigits(a, b, 3);
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
