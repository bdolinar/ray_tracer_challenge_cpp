#include <catch2/catch.hpp>

#include <raytracer/intersection.h>
#include <raytracer/transform.h>

TEST_CASE("A ray intersects a sphere at two points", "[spheres]")
{
  Ray r(point(0, 0, -5), vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].t() == 4.0);
  CHECK(xs[1].t() == 6.0);
}

TEST_CASE("A ray intersects a sphere at a tangent", "[spheres]")
{
  Ray r(point(0, 1, -5), vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].t() == 5.0);
  CHECK(xs[1].t() == 5.0);
}

TEST_CASE("A ray misses a sphere", "[spheres]")
{
  Ray r(point(0, 2, -5), vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.intersect(r);
  CHECK(xs.empty());
}

TEST_CASE("A ray originates inside a sphere", "[spheres]")
{
  Ray r(point(0, 0, 0), vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].t() == -1.0);
  CHECK(xs[1].t() == 1.0);
}

TEST_CASE("A sphere is behind a ray", "[spheres]")
{
  Ray r(point(0, 0, 5), vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].t() == -6.0);
  CHECK(xs[1].t() == -4.0);
}

TEST_CASE("intersect sets the object on the intersection", "[spheres]")
{
  Ray r(point(0, 0, -5), vector(0, 0, 1));
  Sphere s;
  Intersections xs = s.intersect(r);
  CHECK(xs.size() == 2);
  CHECK(&xs[0].object() == &s);
  CHECK(&xs[1].object() == &s);
}

TEST_CASE("A sphere's default transformation", "[spheres]")
{
  Sphere s;
  CHECK(s.transform() == Matrix::identity_matrix(4));
}

TEST_CASE("Changing a sphere's transformation", "[spheres]")
{
  Sphere s;
  Matrix t = translation(2, 3, 4);
    s.set_transform(t);
  CHECK(s.transform() == t);
}

TEST_CASE("Intersecting a scaled sphere with a ray", "[spheres]")
{
  Ray r(point(0, 0, -5), vector(0, 0, 1));
  Sphere s;
    s.set_transform(scaling(2, 2, 2));
  Intersections xs = s.intersect(r);
  CHECK(xs.size() == 2);
  CHECK(xs[0].t() == 3);
  CHECK(xs[1].t() == 7);
}

TEST_CASE("Intersecting a translated sphere with a ray", "[spheres]")
{
  Ray r(point(0, 0, -5), vector(0, 0, 1));
  Sphere s;
    s.set_transform(translation(5, 0, 0));
  Intersections xs = s.intersect(r);
  CHECK(xs.empty());
}

TEST_CASE("The normal on a sphere at a point on the x axis", "[spheres]")
{
  Sphere s;
  Tuple n = s.normal_at(point(1, 0, 0));
  CHECK(n == vector(1, 0, 0));
}

TEST_CASE("The normal on a sphere at a point on the y axis", "[spheres]")
{
  Sphere s;
  Tuple n = s.normal_at(point(0, 1, 0));
  CHECK(n == vector(0, 1, 0));
}

TEST_CASE("The normal on a sphere at a point on thezaxis", "[spheres]")
{
  Sphere s;
  Tuple n = s.normal_at(point(0, 0, 1));
  CHECK(n == vector(0, 0, 1));
}

TEST_CASE("The normal on a sphere at a non-axial point", "[spheres]")
{
  Sphere s;
  Tuple n = s.normal_at(point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
  CHECK(n == vector(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
}

TEST_CASE("The normal is a normalized vector", "[spheres]")
{
  Sphere s;
  Tuple n = s.normal_at(point(sqrt(3)/3, sqrt(3)/3, sqrt(3)/3));
  CHECK(n == n.normalize());
}

TEST_CASE("Computing the normal on a translated sphere", "[spheres]")
{
  Sphere s;
    s.set_transform(translation(0, 1, 0));
  Tuple n = s.normal_at(point(0, 1.70711, -0.70711));
  CHECK(approximately_equal(n, vector(0, 0.70711, -0.70711)));
}

TEST_CASE("Computing the normal on a transformed sphere", "[spheres]")
{
  Sphere s;
  Matrix m = scaling(1, 0.5, 1) * rotation_z(M_PI / 5);
    s.set_transform(m);
  Tuple n = s.normal_at(point(0, sqrt(2)/2, -sqrt(2)/2));
  CHECK(approximately_equal(n, vector(0, 0.97014, -0.24254)));
}

TEST_CASE("A sphere has a default material", "[spheres]")
{
  Sphere s;
  Material m = s.material();
  CHECK(m == Material());
}

TEST_CASE("A sphere may be assigned a material", "[spheres]")
{
  Sphere s;
  Material m;
  m.set_ambient(1);
    s.set_material(m);
  CHECK(s.material() == m);
}

#if 0
TEST_CASE("A helper for producing a sphere with a glassy material", "[spheres]")
{
  auto s = glass_sphere();
  CHECK(s.transform == identity_matrix);
  CHECK(s.material.transparency == 1.0);
  CHECK(s.material.refractive_index == 1.5);
}
#endif
