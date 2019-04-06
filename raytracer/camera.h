#pragma once

#include <raytracer/canvas.h>
#include <raytracer/matrix.h>
#include <raytracer/ray.h>
#include <raytracer/world.h>

/// Camera describing where the world will be rendered from.
class Camera
{
public:
  /// Construct a camera.
  /// \param hsize The horizontal size in pixels.
  /// \param vsize The vertical size in pixels.
  /// \param fieldOfView The field of view in radians.
  Camera(int hsize, int vsize, double fieldOfView);

  /// Get the orizontal size.
  /// \return The horizontal size in pixels.
  int HSize() const { return hSize_; }

  /// Set the horizontal size.
  /// \param hSize The horizontal size in pixels.
  void HSize(int hSize) { hSize_ = hSize; }

  /// Get the vertical size.
  /// \return The vertical size in pixels.
  int VSize() const { return vSize_; }

  /// Set the vertical size.
  /// \param vSize The vertical size in pixels.
  void VSize(int vSize) { vSize_ = vSize; }

  /// Get the field of view.
  /// \return The field of view.
  double FieldOfView() const { return fieldOfView_; }

  /// Set the field of view.
  /// \param fieldOfView The field of view.
  void FieldOfView(double fieldOfView) { fieldOfView_ = fieldOfView; }

  /// Get the transformation matrix of the world.
  /// \return The transformation matrix of the world.
  const Matrix& Transform() const { return transform_; }

  /// Set the transformation matrix of the world.
  /// \param transform The transformation matrix of the world.
  void Transform(const Matrix& transform) { transform_ = transform; }

  /// Get the world size of a pixel.
  /// \return The world size of a pixel.
  double PixelSize() const;

  /// Build a ray from the camera eye through a pixel.
  /// \param px The X coordinate of the pixel.
  /// \param py The Y coordinate of the pixel.
  /// \return The ray from the camera eye through the given pixel.
  Ray RayForPixel(double px, double py);

  /// Render the world.
  /// \param world The world to render.
  /// \return The canvas of rendered pixels.
  Canvas Render(const World& world);

private:
  void CalculatePixelData();

  int hSize_;           ///< The horizontal size in pixels.
  int vSize_;           ///< The vertical size in pixels.
  double fieldOfView_;  ///< The field of view.
  Matrix transform_;    ///< The world transformation matrix.
  double halfWidth_;    ///< Half the width of the view.
  double halfHeight_;   ///< Half the hight of the view.
  double pixelSize_;    ///< The world size of a pixel.
};
