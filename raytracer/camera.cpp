#include <raytracer/camera.h>

#include <cmath>


//------------------------------------------------------------------------------
Camera::Camera(int a_h_size, int a_v_size, double a_field_of_view)
    : h_size_(a_h_size)
      , v_size_(a_v_size)
      , field_of_view_(a_field_of_view)
      , transform_(Matrix::identity_matrix())
      , half_width_(0.0)
      , half_height_(0.0)
      , pixel_size_(0.0)
{
  calculate_pixel_data();
}

//------------------------------------------------------------------------------
double Camera::pixel_size() const
{
  return pixel_size_;
}

//------------------------------------------------------------------------------
Ray Camera::ray_for_pixel(double a_px, double a_py) const
{
  // the offset from the edge of the canvas to the pixel's center
  double x_offset = (a_px + 0.5) * pixel_size();
  double y_offset = (a_py + 0.5) * pixel_size();

  // the untransformed coordinates of the pixel in world space.
  // (remember that the camera looks toward -z_, so +x_ is to the *left*.)
  double world_x = half_width_ - x_offset;
  double world_y = half_height_ - y_offset;

  // using the camera matrix, set_transform the canvas point and the origin,
  // and then compute the ray's direction vector.
  // (remember that the canvas is at z_=-1)
  Tuple pixel = transform().inverse() * point(world_x, world_y, -1);
  Tuple origin = transform().inverse() * point(0, 0, 0);
  Tuple direction = (pixel - origin).normalize();
  return {origin, direction};
}

//------------------------------------------------------------------------------
void Camera::calculate_pixel_data()
{
  double half_view = tan(field_of_view_ / 2);
  double aspect = (double) h_size_ / v_size_;
  if (aspect >= 1)
  {
    half_width_ = half_view;
    half_height_ = half_view / aspect;
  }
  else
  {
    half_width_ = half_view * aspect;
    half_height_ = half_view;
  }

  pixel_size_ = (half_width_ * 2) / h_size_;
}

//------------------------------------------------------------------------------
Canvas Camera::render(const World& a_world) const
{
  Canvas image(h_size_, v_size_);
  for (int y = 0; y < v_size_; ++y)
  {
    for (int x = 0; x < h_size_; ++x)
    {
      Ray ray = ray_for_pixel(x, y);
      Color color = a_world.color_at(ray);
      image.write_pixel(x, y, color);
    }
  }
  return image;
}
