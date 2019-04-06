#pragma once

#include <cmath>

class Matrix;
class Tuple;

/// \brief Build transformation matrix for translation.
/// \param[in] xTranslation The offset to translate x coordinate.
/// \param[in] yTranslation The offset to translate y coordinate.
/// \param[in] zTranslation The offset to translate z coordinate.
/// \return The translation transformation matrix.
Matrix Translation(double xTranslation, double yTranslation, double zTranslation);

/// \brief Build transformation matrix for scaling.
/// \param[in] xScale The factor to scale x coordinate.
/// \param[in] yScale The factor to scale y coordinate.
/// \param[in] zScale The factor to scale z coordinate.
/// \return The scaling transformation matrix.
Matrix Scaling(double xScale, double yScale, double zScale);

/// \brief Build transformation matrix for rotation about the x-axis.
/// \param[in] radians The amount to rotate in radians.
/// \return The rotation transformation matrix.
Matrix RotationX(double radians);

/// \brief Build transformation matrix for rotation about the y-axis.
/// \param[in] radians The amount to rotate in radians.
/// \return The rotation transformation matrix.
Matrix RotationY(double radians);

/// \brief Build transformation matrix for rotation about the z-axis.
/// \param[in] radians The amount to rotate in radians.
/// \return The rotation transformation matrix.
Matrix RotationZ(double radians);

/// \brief Build transformation matrix for shearing.
/// \param[in] xy Shear of x in proportion to y.
/// \param[in] xz Shear of x in proportion to z.
/// \param[in] yx Shear of y in proportion to x.
/// \param[in] yz Shear of y in proportion to z.
/// \param[in] zx Shear of z in proportion to x.
/// \param[in] zy Shear of z in proportion to y.
/// \return The shearing transformation matrix.
Matrix Shearing(double xy, double xz, double yx, double yz, double zx, double zy);

/// \brief Build view transformation matrix.
/// \param from The point looked from (where the eye is located).
/// \param to The point be looked at.
/// \param up A vector in the up direction.
/// \return A transformation matrix that moves the view to default location
/// (from: (0, 0, 0), to: (0, 0, -1), and up: (0, 1, 0).
Matrix ViewTransform(const Tuple& from, const Tuple& to, const Tuple& up);
