#include <catch2/catch.hpp>

#include <raytracer/camera.h>
#include <raytracer/matrix.h>
#include <raytracer/test_utils.h>
#include <raytracer/transform.h>
#include <raytracer/world.h>

TEST_CASE("Constructing a camera", "[camera]")
{
  int hSize = 160;
  int vSize = 120;
  double field_of_view = M_PI/2;
  Camera c(hSize, vSize, field_of_view);
  CHECK(c.HSize() == 160);
  CHECK(c.VSize() == 120);
  CHECK(c.FieldOfView() == M_PI/2);
  CHECK(c.Transform() == Matrix::IdentityMatrix());
}

TEST_CASE("The pixel size for a horizontal canvas", "[camera]")
{
  Camera c(200, 125, M_PI/2);
  CHECK(NearlyEqual(c.PixelSize(), 0.01));
}

TEST_CASE("The pixel size for a vertical canvas", "[camera]")
{
  Camera c(125, 200, M_PI/2);
  double pixelSize = c.PixelSize();
  CHECK(NearlyEqual(pixelSize, 0.01));
}

TEST_CASE("Constructing a ray through the center of the canvas", "[camera]")
{
  Camera c(201, 101, M_PI/2);
  Ray r = c.RayForPixel(100, 50);
  CHECK(r.Origin() == Point(0, 0, 0));
  CHECK(NearlyEqual(r.Direction(), Vector(0, 0, -1)));
}

TEST_CASE("Constructing a ray through a corner of the canvas", "[camera]")
{
  Camera c(201, 101, M_PI/2);
  Ray r = c.RayForPixel(0, 0);
  CHECK(r.Origin() == Point(0, 0, 0));
  CHECK(ApproximatelyEqual(r.Direction(), Vector(0.66519, 0.33259, -0.66851)));
}

TEST_CASE("Constructing a ray when the camera is transformed", "[camera]")
{
  Camera c(201, 101, M_PI/2);
  c.Transform(RotationY(M_PI/4) * Translation(0, -2, 5));
  Ray r = c.RayForPixel(100, 50);
  CHECK(r.Origin() == Point(0, 2, -5));
  CHECK(ApproximatelyEqual(r.Direction(), Vector(sqrt(2)/2, 0, -sqrt(2)/2)));
}

TEST_CASE("Rendering a world with a camera", "[camera]")
{
  World w = DefaultWorld();
  Camera c(11, 11, M_PI/2);
  Tuple from = Point(0, 0, -5);
  Tuple to = Point(0, 0, 0);
  Tuple up = Vector(0, 1, 0);
  c.Transform(ViewTransform(from, to, up));
  auto image = c.Render(w);
  CHECK(ApproximatelyEqual(image.PixelAt(5, 5), Color(0.38066, 0.47583, 0.2855)));
}
