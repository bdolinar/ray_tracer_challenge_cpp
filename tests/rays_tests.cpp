#include <catch2/catch.hpp>

#include <raytracer/matrix.h>
#include <raytracer/ray.h>
#include <raytracer/transform.h>

TEST_CASE("Creating and querying a ray", "[rays]")
{
  Tuple origin = point(1, 2, 3);
  Tuple direction = vector(4, 5, 6);
  Ray r(origin, direction);
  CHECK(r.origin() == origin);
  CHECK(r.direction() == direction);
}

TEST_CASE("Computing a point from a distance", "[rays]")
{
  Ray r(point(2, 3, 4), vector(1, 0, 0));
  CHECK(r.position(0) == point(2, 3, 4));
  CHECK(r.position(1) == point(3, 3, 4));
  CHECK(r.position(-1) == point(1, 3, 4));
  CHECK(r.position(2.5) == point(4.5, 3, 4));
}

TEST_CASE("Translating a ray", "[rays]")
{
  Ray r(point(1, 2, 3), vector(0, 1, 0));
  Matrix m = translation(3, 4, 5);
  Ray r2 = r.transform(m);
  CHECK(r2.origin() == point(4, 6, 8));
  CHECK(r2.direction() == vector(0, 1, 0));
}

TEST_CASE("scaling a ray", "[rays]")
{
  Ray r(point(1, 2, 3), vector(0, 1, 0));
  Matrix m = scaling(2, 3, 4);
  Ray r2 = r.transform(m);
  CHECK(r2.origin() == point(2, 6, 12));
  CHECK(r2.direction() == vector(0, 3, 0));
}
