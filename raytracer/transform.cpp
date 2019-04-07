#include <raytracer/transform.h>

#include <raytracer/matrix.h>


//------------------------------------------------------------------------------
Matrix translation(double a_x_translation, double a_y_translation,
                   double a_z_translation)
{
  Matrix t = Matrix::identity_matrix(4);
  t[0][3] = a_x_translation;
  t[1][3] = a_y_translation;
  t[2][3] = a_z_translation;
  return t;
}

//------------------------------------------------------------------------------
Matrix scaling(double a_x_scale, double a_y_scale, double a_z_scale)
{
  Matrix t;
  t[0][0] = a_x_scale;
  t[1][1] = a_y_scale;
  t[2][2] = a_z_scale;
  t[3][3] = 1.0;
  return t;
}

//------------------------------------------------------------------------------
Matrix rotation_x(double a_radians)
{
  Matrix t;
  double cos_r = cos(a_radians);
  double sin_r = sin(a_radians);
  t[0][0] = 1.0;
  t[1][1] = cos_r;
  t[2][2] = cos_r;
  t[2][1] = sin_r;
  t[1][2] = -sin_r;
  t[3][3] = 1.0;
  return t;
}

//------------------------------------------------------------------------------
Matrix rotation_y(double a_radians)
{
  Matrix t;
  double cos_r = cos(a_radians);
  double sin_r = sin(a_radians);
  t[0][0] = cos_r;
  t[0][2] = sin_r;
  t[2][0] = -sin_r;
  t[2][2] = cos_r;
  t[1][1] = 1.0;
  t[3][3] = 1.0;
  return t;
}

//------------------------------------------------------------------------------
Matrix rotation_z(double a_radians)
{
  Matrix t;
  double cos_r = cos(a_radians);
  double sin_r = sin(a_radians);
  t[0][0] = cos_r;
  t[1][1] = cos_r;
  t[1][0] = sin_r;
  t[0][1] = -sin_r;
  t[2][2] = 1.0;
  t[3][3] = 1.0;
  return t;
}

//------------------------------------------------------------------------------
Matrix shearing(double a_xy, double a_xz, double a_yx, double a_yz, double a_zx,
                double a_zy)
{
  Matrix t = Matrix::identity_matrix(4);
  t[0][1] = a_xy;
  t[0][2] = a_xz;
  t[1][0] = a_yx;
  t[1][2] = a_yz;
  t[2][0] = a_zx;
  t[2][1] = a_zy;
  return t;
}

//------------------------------------------------------------------------------
Matrix view_transform(const Tuple& a_look_from, const Tuple& a_look_to,
                      const Tuple& a_up)
{
  Tuple forward = (a_look_to - a_look_from).normalize();
  Tuple upn = a_up.normalize();
  Tuple left = cross(forward, upn);
  Tuple true_up = cross(left, forward);
  Matrix orientation = {
      {left.x(),     left.y(),     left.z(),     0},
      {true_up.x(),  true_up.y(),  true_up.z(),  0},
      {-forward.x(), -forward.y(), -forward.z(), 0},
      {0,            0,            0,            1}};
  return orientation *
         translation(-a_look_from.x(), -a_look_from.y(), -a_look_from.z());
}
