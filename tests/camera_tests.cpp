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
  CHECK(c.h_size() == 160);
  CHECK(c.v_size() == 120);
  CHECK(c.field_of_view() == M_PI/2);
  CHECK(c.transform() == Matrix::identity_matrix());
}

TEST_CASE("The pixel size for a horizontal canvas", "[camera]")
{
  Camera c(200, 125, M_PI/2);
  CHECK(nearly_equal(c.pixel_size(), 0.01));
}

TEST_CASE("The pixel size for a vertical canvas", "[camera]")
{
  Camera c(125, 200, M_PI/2);
  double pixelSize = c.pixel_size();
  CHECK(nearly_equal(pixelSize, 0.01));
}

TEST_CASE("Constructing a ray through the center of the canvas", "[camera]")
{
  Camera c(201, 101, M_PI/2);
  Ray r = c.ray_for_pixel(100, 50);
  CHECK(r.origin() == point(0, 0, 0));
  CHECK(nearly_equal(r.direction(), vector(0, 0, -1)));
}

TEST_CASE("Constructing a ray through a corner of the canvas", "[camera]")
{
  Camera c(201, 101, M_PI/2);
  Ray r = c.ray_for_pixel(0, 0);
  CHECK(r.origin() == point(0, 0, 0));
  CHECK(approximately_equal(r.direction(), vector(0.66519, 0.33259, -0.66851)));
}

TEST_CASE("Constructing a ray when the camera is transformed", "[camera]")
{
  Camera c(201, 101, M_PI/2);
    c.set_transform(rotation_y(M_PI / 4) * translation(0, -2, 5));
  Ray r = c.ray_for_pixel(100, 50);
  CHECK(r.origin() == point(0, 2, -5));
  CHECK(approximately_equal(r.direction(), vector(sqrt(2)/2, 0, -sqrt(2)/2)));
}

TEST_CASE("Rendering a world with a camera", "[camera]")
{
  World w = default_world();
  Camera c(11, 11, M_PI/2);
  Tuple from = point(0, 0, -5);
  Tuple to = point(0, 0, 0);
  Tuple up = vector(0, 1, 0);
    c.set_transform(view_transform(from, to, up));
  auto image = c.render(w);
  CHECK(approximately_equal(image.pixel_at(5, 5), Color(0.38066, 0.47583, 0.2855)));
}
