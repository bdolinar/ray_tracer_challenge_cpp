#pragma once

#include <cmath>

class Matrix;

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
