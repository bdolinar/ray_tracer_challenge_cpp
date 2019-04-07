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
  /// \param a_h_size The horizontal size in pixels.
  /// \param a_v_size The vertical size in pixels.
  /// \param a_field_of_view The field of view in radians.
  Camera(int a_h_size, int a_v_size, double a_field_of_view);

  /// Get the horizontal size.
  /// \return The horizontal size in pixels.
  int h_size() const
  {
    return h_size_;
  }

  /// Set the horizontal size.
  /// \param a_h_size The horizontal size in pixels.
  void set_h_size(int a_h_size)
  {
    h_size_ = a_h_size;
  }

  /// Get the vertical size.
  /// \return The vertical size in pixels.
  int v_size() const
  {
    return v_size_;
  }

  /// Set the vertical size.
  /// \param a_v_size The vertical size in pixels.
  void set_v_size(int a_v_size)
  {
    v_size_ = a_v_size;
  }

  /// Get the field of view.
  /// \return The field of view.
  double field_of_view() const
  {
    return field_of_view_;
  }

  /// Set the field of view.
  /// \param a_field_of_view The field of view.
  void set_field_of_view(double a_field_of_view)
  {
    field_of_view_ = a_field_of_view;
  }

  /// Get the transformation matrix of the world.
  /// \return The transformation matrix of the world.
  const Matrix& transform() const
  {
    return transform_;
  }

  /// Set the transformation matrix of the world.
  /// \param a_transform The transformation matrix of the world.
  void set_transform(const Matrix& a_transform)
  {
    transform_ = a_transform;
  }

  /// Get the world size of a pixel.
  /// \return The world size of a pixel.
  double pixel_size() const;

  /// Build a ray from the camera eye through a pixel.
  /// \param a_px The X coordinate of the pixel.
  /// \param a_py The Y coordinate of the pixel.
  /// \return The ray from the camera eye through the given pixel.
  Ray ray_for_pixel(double a_px, double a_py) const;

  /// Render the world.
  /// \param a_world The world to render.
  /// \return The canvas of rendered pixels.
  Canvas render(const World& a_world) const;

private:
  void calculate_pixel_data();

  int h_size_;            ///< The horizontal size in pixels.
  int v_size_;            ///< The vertical size in pixels.
  double field_of_view_;  ///< The field of view.
  Matrix transform_;      ///< The world transformation matrix.
  double half_width_;     ///< Half the width of the view.
  double half_height_;    ///< Half the height of the view.
  double pixel_size_;     ///< The world size of a pixel.
};
