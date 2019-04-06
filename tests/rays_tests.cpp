#include <catch2/catch.hpp>

#include <raytracer/matrix.h>
#include <raytracer/ray.h>
#include <raytracer/transform.h>

TEST_CASE("Creating and querying a ray", "[rays]")
{
  Tuple origin = Point(1, 2, 3);
  Tuple direction = Vector(4, 5, 6);
  Ray r(origin, direction);
  CHECK(r.Origin() == origin);
  CHECK(r.Direction() == direction);
}

TEST_CASE("Computing a point from a distance", "[rays]")
{
  Ray r(Point(2, 3, 4), Vector(1, 0, 0));
  CHECK(r.Position(0) == Point(2, 3, 4));
  CHECK(r.Position(1) == Point(3, 3, 4));
  CHECK(r.Position(-1) == Point(1, 3, 4));
  CHECK(r.Position(2.5) == Point(4.5, 3, 4));
}

TEST_CASE("Translating a ray", "[rays]")
{
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  Matrix m = Translation(3, 4, 5);
  Ray r2 = r.Transform(m);
  CHECK(r2.Origin() == Point(4, 6, 8));
  CHECK(r2.Direction() == Vector(0, 1, 0));
}

TEST_CASE("Scaling a ray", "[rays]")
{
  Ray r(Point(1, 2, 3), Vector(0, 1, 0));
  Matrix m = Scaling(2, 3, 4);
  Ray r2 = r.Transform(m);
  CHECK(r2.Origin() == Point(2, 6, 12));
  CHECK(r2.Direction() == Vector(0, 3, 0));
}
