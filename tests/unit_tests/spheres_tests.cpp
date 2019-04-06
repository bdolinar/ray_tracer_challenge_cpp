#include <catch2/catch.hpp>

#include "intersection.h"
#include "matrix.h"
#include "ray.h"
#include "sphere.h"
#include "transform.h"
#include "tuple.h"

TEST_CASE("A ray intersects a sphere at two points", "[spheres]")
{
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.Intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].T() == 4.0);
  CHECK(xs[1].T() == 6.0);
}

TEST_CASE("A ray intersects a sphere at a tangent", "[spheres]")
{
  Ray r(Point(0, 1, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.Intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].T() == 5.0);
  CHECK(xs[1].T() == 5.0);
}

TEST_CASE("A ray misses a sphere", "[spheres]")
{
  Ray r(Point(0, 2, -5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.Intersect(r);
  CHECK(xs.size() == 0);
}

TEST_CASE("A ray originates inside a sphere", "[spheres]")
{
  Ray r(Point(0, 0, 0), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.Intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].T() == -1.0);
  CHECK(xs[1].T() == 1.0);
}

TEST_CASE("A sphere is behind a ray", "[spheres]")
{
  Ray r(Point(0, 0, 5), Vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.Intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].T() == -6.0);
  CHECK(xs[1].T() == -4.0);
}

TEST_CASE("Intersect sets the object on the intersection", "[spheres]")
{
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  auto xs = s.Intersect(r);
  CHECK(xs.size() == 2);
  CHECK(&xs[0].Object() == &s);
  CHECK(&xs[1].Object() == &s);
}

TEST_CASE("A sphere's default transformation", "[spheres]")
{
  Sphere s;
  CHECK(s.Transform() == Matrix::IdentityMatrix(4));
}

TEST_CASE("Changing a sphere's transformation", "[spheres]")
{
  Sphere s;
  Matrix t = Translation(2, 3, 4);
  s.Transform(t);
  CHECK(s.Transform() == t);
}

TEST_CASE("Intersecting a scaled sphere with a ray", "[spheres]")
{
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  s.Transform(Scaling(2, 2, 2));
  Intersections xs = s.Intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].T() == 3);
  CHECK(xs[1].T() == 7);
}

TEST_CASE("Intersecting a translated sphere with a ray", "[spheres]")
{
  Ray r(Point(0, 0, -5), Vector(0, 0, 1));
  Sphere s;
  s.Transform(Translation(5, 0, 0));
  Intersections xs = s.Intersect(r);
  CHECK(xs.size() == 0);
}

#if 0
TEST_CASE("The normal on a sphere at a point on the x axis", "[spheres]")
{
  Sphere s;
  auto n = normal_at(s, Point(1, 0, 0));
  CHECK(n == Vector(1, 0, 0));
}

TEST_CASE("The normal on a sphere at a point on the y axis", "[spheres]")
{
  Sphere s;
  auto n = normal_at(s, Point(0, 1, 0));
  CHECK(n == Vector(0, 1, 0));
}

TEST_CASE("The normal on a sphere at a point on the z axis", "[spheres]")
{
  Sphere s;
  auto n = normal_at(s, Point(0, 0, 1));
  CHECK(n == Vector(0, 0, 1));
}

TEST_CASE("The normal on a sphere at a non-axial point", "[spheres]")
{
  Sphere s;
  auto n = normal_at(s, Point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
  CHECK(n == Vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
}

TEST_CASE("The normal is a normalized vector", "[spheres]")
{
  Sphere s;
  auto n = normal_at(s, Point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
  CHECK(n == normalize(n));
}

TEST_CASE("Computing the normal on a translated sphere", "[spheres]")
{
  Sphere s;
  set_transform(s, translation(0, 1, 0));
  auto n = normal_at(s, Point(0, 1.70711, -0.70711));
  CHECK(n == Vector(0, 0.70711, -0.70711));
}

TEST_CASE("Computing the normal on a transformed sphere", "[spheres]")
{
  Sphere s;
  auto m = scaling(1, 0.5, 1) * rotation_z(M_PI/5);
  set_transform(s, m);
  auto n = normal_at(s, Point(0, sqrt(2)/2, -sqrt(2)/2));
  CHECK(n == Vector(0, 0.97014, -0.24254));
}

TEST_CASE("A sphere has a default material", "[spheres]")
{
  Sphere s;
  auto m = s.material;
  CHECK(m == material());
}

TEST_CASE("A sphere may be assigned a material", "[spheres]")
{
  Sphere s;
  auto m = material();
  auto m.ambient = 1;
  auto s.material = m;
  CHECK(s.material == m);
}

TEST_CASE("A helper for producing a sphere with a glassy material", "[spheres]")
{
  auto s = glass_sphere();
  CHECK(s.transform == identity_matrix);
  CHECK(s.material.transparency == 1.0);
  CHECK(s.material.refractive_index == 1.5);
}
#endif
