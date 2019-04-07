#include <raytracer/tuple.h>

#include <algorithm>
#include <cmath>
#include <raytracer/test_utils.h>


//------------------------------------------------------------------------------
bool Tuple::is_point() const
{
  return w_ == 1.0;
}

//------------------------------------------------------------------------------
bool Tuple::is_vector() const
{
  return w_ == 0.0;
}

//------------------------------------------------------------------------------
double Tuple::magnitude() const
{
  return sqrt(x_ * x_ + y_ * y_ + z_ * z_ + w_ * w_);
}

//------------------------------------------------------------------------------
Tuple Tuple::normalize() const
{
  double mag = magnitude();
  return {x_ / mag, y_ / mag, z_ / mag, w_ / mag};
}

//------------------------------------------------------------------------------
bool Tuple::operator==(const Tuple& a_rhs) const
{
  return std::tie(x_, y_, z_, w_) ==
         std::tie(a_rhs.x_, a_rhs.y_, a_rhs.z_, a_rhs.w_);
}

//------------------------------------------------------------------------------
bool Tuple::operator!=(const Tuple& a_rhs) const
{
  return !(a_rhs == *this);
}

//------------------------------------------------------------------------------
double dot(const Tuple& a_lhs, const Tuple& a_rhs)
{
  double result =
      a_lhs.x_ * a_rhs.x_ + a_lhs.y_ * a_rhs.y_ + a_lhs.z_ * a_rhs.z_ +
      a_lhs.w_ * a_rhs.w_;
  return result;
}

//------------------------------------------------------------------------------
Tuple cross(const Tuple& a_lhs, const Tuple& a_rhs)
{
  return vector(a_lhs.y_ * a_rhs.z_ - a_lhs.z_ * a_rhs.y_,
                a_lhs.z_ * a_rhs.x_ - a_lhs.x_ * a_rhs.z_,
                a_lhs.x_ * a_rhs.y_ - a_lhs.y_ * a_rhs.x_);
}

//------------------------------------------------------------------------------
Tuple reflect(const Tuple& a_in_vector, const Tuple& a_normal)
{
  return a_in_vector - a_normal * 2 * dot(a_in_vector, a_normal);
}

//------------------------------------------------------------------------------
bool approximately_equal(const Tuple& a_lhs, const Tuple& a_rhs)
{
  bool equal_x = equal_to_digits(a_lhs.x_, a_rhs.x_, 4);
  bool equal_y = equal_to_digits(a_lhs.y_, a_rhs.y_, 4);
  bool equal_z = equal_to_digits(a_lhs.z_, a_rhs.z_, 4);
  bool equal_w = equal_to_digits(a_lhs.w_, a_rhs.w_, 4);
  return equal_x && equal_y && equal_z && equal_w;
}

//------------------------------------------------------------------------------
bool nearly_equal(const Tuple& a_lhs, const Tuple& a_rhs)
{
  bool equal_x = equal_to_digits(a_lhs.x_, a_rhs.x_, 10);
  bool equal_y = equal_to_digits(a_lhs.y_, a_rhs.y_, 10);
  bool equal_z = equal_to_digits(a_lhs.z_, a_rhs.z_, 10);
  bool equal_w = equal_to_digits(a_lhs.w_, a_rhs.w_, 10);
  return equal_x && equal_y && equal_z && equal_w;
}
