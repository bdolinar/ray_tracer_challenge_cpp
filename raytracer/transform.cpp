#include <raytracer/transform.h>

#include <raytracer/matrix.h>


Matrix Translation(double xTranslation, double yTranslation, double zTranslation)
{
  Matrix t = Matrix::IdentityMatrix(4);
  t[0][3] = xTranslation;
  t[1][3] = yTranslation;
  t[2][3] = zTranslation;
  return t;
}


Matrix Scaling(double xScale, double yScale, double zScale)
{
  Matrix t;
  t[0][0] = xScale;
  t[1][1] = yScale;
  t[2][2] = zScale;
  t[3][3] = 1.0;
  return t;
}


Matrix RotationX(double radians)
{
  Matrix t;
  double cos_r = cos(radians);
  double sin_r = sin(radians);
  t[0][0] = 1.0;
  t[1][1] = cos_r;
  t[2][2] = cos_r;
  t[2][1] = sin_r;
  t[1][2] = -sin_r;
  t[3][3] = 1.0;
  return t;
}


Matrix RotationY(double radians)
{
  Matrix t;
  double cos_r = cos(radians);
  double sin_r = sin(radians);
  t[0][0] = cos_r;
  t[0][2] = sin_r;
  t[2][0] = -sin_r;
  t[2][2] = cos_r;
  t[1][1] = 1.0;
  t[3][3] = 1.0;
  return t;
}


Matrix RotationZ(double radians)
{
  Matrix t;
  double cos_r = cos(radians);
  double sin_r = sin(radians);
  t[0][0] = cos_r;
  t[1][1] = cos_r;
  t[1][0] = sin_r;
  t[0][1] = -sin_r;
  t[2][2] = 1.0;
  t[3][3] = 1.0;
  return t;
}


Matrix Shearing(double xy, double xz, double yx, double yz, double zx, double zy)
{
  Matrix t = Matrix::IdentityMatrix(4);
  t[0][1] = xy;
  t[0][2] = xz;
  t[1][0] = yx;
  t[1][2] = yz;
  t[2][0] = zx;
  t[2][1] = zy;
  return t;
}

Matrix ViewTransform(const Tuple& from, const Tuple& to, const Tuple& up)
{
  Tuple forward = (to - from).Normalize();
  Tuple upn = up.Normalize();
  Tuple left = Cross(forward, upn);
  Tuple true_up = Cross(left, forward);
  Matrix orientation = {
    {left.x, left.y, left.z, 0},
    {true_up.x, true_up.y, true_up.z, 0},
    {-forward.x, -forward.y, -forward.z, 0},
    {0, 0, 0, 1}};
  return orientation * Translation(-from.x, -from.y, -from.z);
}
