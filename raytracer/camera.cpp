#include <raytracer/camera.h>

#include <cmath>


Camera::Camera(int hSize, int vSize, double fieldOfView)
: hSize_(hSize)
, vSize_(vSize)
, fieldOfView_(fieldOfView)
, transform_(Matrix::IdentityMatrix())
, halfWidth_(0.0)
, halfHeight_(0.0)
, pixelSize_(0.0)
{
  CalculatePixelData();
}


double Camera::PixelSize() const
{
  return pixelSize_;
}


Ray Camera::RayForPixel(double px, double py)
{
  // the offset from the edge of the canvas to the pixel's center
  double xoffset = (px + 0.5) * PixelSize();
  double yoffset = (py + 0.5) * PixelSize();

  // the untransformed coordinates of the pixel in world space.
  // (remember that the camera looks toward -z, so +x is to the *left*.)
  double world_x = halfWidth_ - xoffset;
  double world_y = halfHeight_ - yoffset;

  // using the camera matrix, transform the canvas point and the origin,
  // and then compute the ray's direction vector.
  // (remember that the canvas is at z=-1)
  Tuple pixel = Transform().Inverse() * Point(world_x, world_y, -1);
  Tuple origin = Transform().Inverse() * Point(0, 0, 0);
  Tuple direction = (pixel - origin).Normalize();
  return {origin, direction};
}


void Camera::CalculatePixelData()
{
  double halfView = tan(fieldOfView_ / 2);
  double aspect = (double)hSize_ / vSize_;
  if (aspect >= 1)
  {
    halfWidth_ = halfView;
    halfHeight_ = halfView / aspect;
  }
  else
  {
    halfWidth_ = halfView * aspect;
    halfHeight_ = halfView;
  }

  pixelSize_ = (halfWidth_ * 2) / hSize_;
}


Canvas Camera::Render(const World& world)
{
  Canvas image(hSize_, vSize_);
  for (int y = 0; y < vSize_; ++y)
  {
    for (int x = 0; x < hSize_; ++x)
    {
      Ray ray = RayForPixel(x, y);
      Color color = world.ColorAt(ray);
      image.WritePixel(x, y, color);
    }
  }
  return image;
}
