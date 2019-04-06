#include "tuple.h"

#include <algorithm>
#include <math.h>

bool Tuple::operator==(const Tuple& rhs) const
{
  bool equalX = EqualToDigits(x, rhs.x, 10);
  bool equalY = EqualToDigits(x, rhs.x, 10);
  bool equalZ = EqualToDigits(x, rhs.x, 10);
  bool equalW = EqualToDigits(x, rhs.x, 10);
  return equalX && equalY && equalZ && equalW;
}

Tuple Point(double x, double y, double z)
{
  Tuple p(x, y, z, 1.0);
  return p;
}

Tuple Vector(double x, double y, double z)
{
  Tuple v(x, y, z, 0.0);
  return v;
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
  double positiveDiff = fabs(a - b);
  double positiveMax = pow(0.1, digits) * std::max(fabs(a), fabs(b));
  return positiveDiff <= positiveMax;
}
