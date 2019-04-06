#pragma once

#include <cmath>

class Matrix;
class Tuple;

/// Build transformation matrix for translation.
/// \param xTranslation The offset to translate x coordinate.
/// \param yTranslation The offset to translate y coordinate.
/// \param zTranslation The offset to translate z coordinate.
/// \return The translation transformation matrix.
Matrix Translation(double xTranslation, double yTranslation, double zTranslation);

/// Build transformation matrix for scaling.
/// \param xScale The factor to scale x coordinate.
/// \param yScale The factor to scale y coordinate.
/// \param zScale The factor to scale z coordinate.
/// \return The scaling transformation matrix.
Matrix Scaling(double xScale, double yScale, double zScale);

/// Build transformation matrix for rotation about the x-axis.
/// \param radians The amount to rotate in radians.
/// \return The rotation transformation matrix.
Matrix RotationX(double radians);

/// Build transformation matrix for rotation about the y-axis.
/// \param radians The amount to rotate in radians.
/// \return The rotation transformation matrix.
Matrix RotationY(double radians);

/// Build transformation matrix for rotation about the z-axis.
/// \param radians The amount to rotate in radians.
/// \return The rotation transformation matrix.
Matrix RotationZ(double radians);

/// Build transformation matrix for shearing.
/// \param xy Shear of x in proportion to y.
/// \param xz Shear of x in proportion to z.
/// \param yx Shear of y in proportion to x.
/// \param yz Shear of y in proportion to z.
/// \param zx Shear of z in proportion to x.
/// \param zy Shear of z in proportion to y.
/// \return The shearing transformation matrix.
Matrix Shearing(double xy, double xz, double yx, double yz, double zx, double zy);

/// Build view transformation matrix.
/// \param from The point looked from (where the eye is located).
/// \param to The point be looked at.
/// \param up A vector in the up direction.
/// \return A transformation matrix that moves the view to default location
/// (from: (0, 0, 0), to: (0, 0, -1), and up: (0, 1, 0).
Matrix ViewTransform(const Tuple& from, const Tuple& to, const Tuple& up);
