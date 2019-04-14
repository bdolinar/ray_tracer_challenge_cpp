#pragma once

#include <cmath>


class Matrix;

class Tuple;

/// Build transformation matrix for translation.
/// \param a_x_translation The offset to translate x coordinate.
/// \param a_y_translation The offset to translate y coordinate.
/// \param a_z_translation The offset to translate z coordinate.
/// \return The translation transformation matrix.
Matrix translation(double a_x_translation, double a_y_translation,
    double a_z_translation);

/// Build transformation matrix for scaling.
/// \param a_x_scale The factor to scale x coordinate.
/// \param a_y_scale The factor to scale y coordinate.
/// \param a_z_scale The factor to scale z coordinate.
/// \return The scaling transformation matrix.
Matrix scaling(double a_x_scale, double a_y_scale, double a_z_scale);

/// Build transformation matrix for rotation about the x-axis.
/// \param a_radians The amount to rotate in radians.
/// \return The rotation transformation matrix.
Matrix rotation_x(double a_radians);

/// Build transformation matrix for rotation about the y-axis.
/// \param a_radians The amount to rotate in radians.
/// \return The rotation transformation matrix.
Matrix rotation_y(double a_radians);

/// Build transformation matrix for rotation about the z-axis.
/// \param a_radians The amount to rotate in radians.
/// \return The rotation transformation matrix.
Matrix rotation_z(double a_radians);

/// Build transformation matrix for shearing.
/// \param a_xy Shear of x in proportion to y.
/// \param a_xz Shear of x in proportion to z.
/// \param a_yx Shear of y in proportion to x.
/// \param a_yz Shear of y in proportion to z.
/// \param a_zx Shear of z in proportion to x.
/// \param a_zy Shear of z in proportion to y.
/// \return The shearing transformation matrix.
Matrix shearing(double a_xy, double a_xz, double a_yx, double a_yz, double a_zx,
    double a_zy);

/// Build view transformation matrix.
/// \param a_look_from The point looked from (where the eye is located).
/// \param a_look_to The point be looked at.
/// \param a_up A vector in the up direction from viewpoint of the eye.
/// \return A transformation matrix that moves the view to default location
/// (from: (0, 0, 0), to: (0, 0, -1), and up: (0, 1, 0).
Matrix view_transform(const Tuple& a_look_from, const Tuple& a_look_to,
    const Tuple& a_up);
