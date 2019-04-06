#include <catch2/catch.hpp>

#include <raytracer/intersection.h>

TEST_CASE("An intersection encapsulates t and object", "[intersections]")
{
  Sphere s;
  Intersection i(3.5, s);
  CHECK(i.T() == 3.5);
  CHECK(&i.Object() == &s);
}

TEST_CASE("Precomputing the state of an intersection", "[intersections]")
{
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere shape;
  Intersection i(4, shape);
  auto comps = i.PrepareComputations(r);
  CHECK(comps.t == i.T());
  CHECK(comps.object == &i.Object());
  CHECK(comps.point == Point(0, 0, -1));
  CHECK(comps.toEye == Vector(0, 0, -1));
  CHECK(comps.normal == Vector(0, 0, -1));
}

#if 0
TEST_CASE("Precomputing the reflection vector", "[intersections]")
{
  auto shape = plane();
  Ray r(Point(0, 1, -1), Vector(0, -sqrt(2)/2, sqrt(2)/2));
  Intersection i(sqrt(2), shape);
  auto comps = prepare_computations(i, r);
  CHECK(comps.reflectv == Vector(0, sqrt(2)/2, sqrt(2)/2));
}
#endif

TEST_CASE("The hit, when an intersection occurs on the outside", "[intersections]")
{
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere shape;
  Intersection i(4, shape);
  auto comps = i.PrepareComputations(r);
  CHECK_FALSE(comps.inside);
}

TEST_CASE("The hit, when an intersection occurs on the inside", "[intersections]")
{
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  Sphere shape;
  Intersection i(1, shape);
  auto comps = i.PrepareComputations(r);
  CHECK(comps.point == Point(0, 0, 1));
  CHECK(comps.toEye == Vector(0, 0, -1));
  CHECK(comps.normal == Vector(0, 0, -1));
  CHECK(comps.inside);
}

#if 0
TEST_CASE("The hit should offset the point", "[intersections]")
{
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  auto shape = sphere() with:;
  Intersection i(5, shape);
  auto comps = prepare_computations(i, r);
  comps.over_point.z < -EPSILON/2
  comps.point.z > comps.over_point.z
}

TEST_CASE("The under point is offset below the surface", "[intersections]")
{
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  auto shape = glass_sphere() with:;
  Intersection i(5, shape);
  Intersections xs = {i};
  auto comps = prepare_computations(i, r, xs);
  comps.under_point.z > EPSILON/2
  comps.point.z < comps.under_point.z
}
#endif

TEST_CASE("Aggregating intersections", "[intersections]")
{
  Sphere s;
  Intersection i1(1, s);
  Intersection i2(2, s);
  Intersections xs = {i1, i2};
  CHECK(xs.size() == 2);
  CHECK(xs[0].T() == 1);
  CHECK(xs[1].T() == 2);
}

TEST_CASE("The hit, when all intersections have positive t", "[intersections]")
{
  Sphere s;
  Intersection i1(1, s);
  Intersection i2(2, s);
  Intersections xs = {i2, i1};
  auto i = Hit(xs);
  REQUIRE(i);
  CHECK(*i == i1);
}

TEST_CASE("The hit, when some intersections have negative t", "[intersections]")
{
  Sphere s;
  Intersection i1(-1, s);
  Intersection i2(1, s);
  Intersections xs = {i2, i1};
  auto i = Hit(xs);
  REQUIRE(i);
  CHECK(*i == i2);
}

TEST_CASE("The hit, when all intersections have negative t", "[intersections]")
{
  Sphere s;
  Intersection i1(-2, s);
  Intersection i2(-1, s);
  Intersections xs = {i2, i1};
  auto i = Hit(xs);
  CHECK(i == nullptr);
}

TEST_CASE("The hit is always the lowest non-negative intersection", "[intersections]")
{
  Sphere s;
  Intersection i1(5, s);
  Intersection i2(7, s);
  Intersection i3(-3, s);
  Intersection i4(2, s);
  Intersections xs = {i1, i2, i3, i4};
  auto i = Hit(xs);
  REQUIRE(i);
  CHECK(*i == i4);
}

#if 0
TEST_CASE("Finding n1 and n2 at various intersections", "[intersections]")
{
  auto A = glass_sphere() with:;
  auto B = glass_sphere() with:;
  auto C = glass_sphere() with:;
  Ray r(Point(0, 0, -4), Vector(0, 0, 1));
  Intersections xs = {{2, A}, {2.75, B}, {3.25, C}, {4.75, B}, {5.25, C}, {6, A}};
  auto comps = prepare_computations(xs[<index>], r, xs);
  CHECK(comps.n1 == <n1>);
  CHECK(comps.n2 == <n2>);
}

TEST_CASE("The Schlick approximation under total internal reflection", "[intersections]")
{
  auto shape = glass_sphere();
  Ray r(Point(0, 0, sqrt(2)/2), Vector(0, 1, 0));
  Intersections xs = {{-sqrt(2)/2, shape}, {sqrt(2)/2, shape}};
  auto comps = prepare_computations(xs[1], r, xs);
  auto reflectance = schlick(comps);
  CHECK(reflectance == 1.0);
}

TEST_CASE("The Schlick approximation with a perpendicular viewing angle", "[intersections]")
{
  auto shape = glass_sphere();
  Ray r(Point(0, 0, 0), Vector(0, 1, 0));
  Intersections xs = {{-1, shape}, {1, shape}};
  auto comps = prepare_computations(xs[1], r, xs);
  auto reflectance = schlick(comps);
  CHECK(reflectance == 0.04);
}

TEST_CASE("The Schlick approximation with small angle and n2 > n1", "[intersections]")
{
  auto shape = glass_sphere();
  Ray r(Point(0, 0.99, -2), Vector(0, 0, 1));
  Intersections xs = {{1.8589, shape}};
  auto comps = prepare_computations(xs[0], r, xs);
  auto reflectance = schlick(comps);
  CHECK(reflectance == 0.48873);
}

TEST_CASE("An intersection can encapsulate `u` and `v`", "[intersections]")
{
  auto s = triangle(Point(0, 1, 0), Point(-1, 0, 0), Point(1, 0, 0));
  auto i = intersection_with_uv(3.5, s, 0.2, 0.4);
  CHECK(i.u == 0.2);
  CHECK(i.v == 0.4);
}
#endif
