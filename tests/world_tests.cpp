#include <catch2/catch.hpp>

#include <raytracer/color.h>
#include <raytracer/intersection.h>
#include <raytracer/light.h>
#include <raytracer/material.h>
#include <raytracer/ray.h>
#include <raytracer/sphere.h>
#include <raytracer/transform.h>
#include <raytracer/world.h>

TEST_CASE("intersect a world with a ray", "[world]")
{
  auto w = default_world();
  Ray r(point(0, 0, -5), vector(0, 0, 1));
  auto xs = w.intersect(r);
  REQUIRE(xs.size() == 4);
  CHECK(xs[0].t() == 4);
  CHECK(xs[1].t() == 4.5);
  CHECK(xs[2].t() == 5.5);
  CHECK(xs[3].t() == 6);
}

TEST_CASE("Shading an intersection", "[world]")
{
  World w = default_world();
  Ray r(point(0, 0, -5), vector(0, 0, 1));
  const Sphere& shape = w.object(0);
  Intersection i(4, shape);
  Computations comps = i.prepare_computations(r);
  Color c = w.shade_hit(comps);
  CHECK(approximately_equal(c, Color(0.38066, 0.47583, 0.2855)));
}

TEST_CASE("Shading an intersection from the inside", "[world]")
{
  World w = default_world();
    w.set_light(Light::new_ptr(point(0, 0.25, 0), Color(1, 1, 1)));
  Ray r(point(0, 0, 0), vector(0, 0, 1));
  const Sphere& shape = w.object(1);
  Intersection i(0.5, shape);
  Computations comps = i.prepare_computations(r);
  Color c = w.shade_hit(comps);
  CHECK(approximately_equal(c, Color(0.90498, 0.90498, 0.90498)));
}

TEST_CASE("The set_color when a ray misses", "[world]")
{
  World w = default_world();
  Ray r(point(0, 0, -5), vector(0, 1, 0));
  Color c = w.color_at(r);
  CHECK(c == Color(0, 0, 0));
}

TEST_CASE("The set_color when a ray hits", "[world]")
{
  World w = default_world();
  Ray r(point(0, 0, -5), vector(0, 0, 1));
  Color c = w.color_at(r);
  CHECK(approximately_equal(c, Color(0.38066, 0.47583, 0.2855)));
}

TEST_CASE("The set_color with an intersection behind the ray", "[world]")
{
  World w = default_world();
  Sphere& outer = w.object(0);
  Material outerMaterial = outer.material();
  outerMaterial.set_ambient(1);
    outer.set_material(outerMaterial);
  Sphere& inner = w.object(1);
  Material innerMaterial = inner.material();
  innerMaterial.set_ambient(1);
    inner.set_material(innerMaterial);
  Ray r(point(0, 0, 0.75), vector(0, 0, -1));
  Color c = w.color_at(r);
  CHECK(c == innerMaterial.color());
}

TEST_CASE("There is no shadow when nothing is collinear with point and light", "[world]")
{
  World w = default_world();
  Tuple p = point(0, 10, 0);
  CHECK_FALSE(w.is_shadowed(p));
}

TEST_CASE("The shadow when an object is between the point and the light", "[world]")
{
  World w = default_world();
  Tuple p = point(10, -10, 10);
  CHECK(w.is_shadowed(p));
}

TEST_CASE("There is no shadow when an object is behind the light", "[world]")
{
  World w = default_world();
  Tuple p = point(-20, 20, -20);
  CHECK_FALSE(w.is_shadowed(p));
}

TEST_CASE("There is no shadow when an object is behind the point", "[world]")
{
  World w = default_world();
  Tuple p = point(-2, 2, -2);
  CHECK_FALSE(w.is_shadowed(p));
}

TEST_CASE("shade_hit() is given an intersection in shadow", "[world]")
{
  World w;
  auto light = Light::new_ptr(point(0, 0, -10), Color(1, 1, 1));
  w.set_light(std::move(light));
  auto s1 = Sphere::new_ptr();
  w.add_object(std::move(s1));
  auto s2 = Sphere::new_ptr();
  s2->set_transform(translation(0, 0, 10));
  w.add_object(std::move(s2));
  Ray r(point(0, 0, 5), vector(0, 0, 1));
  Intersection i(4, w.object(1));
  Computations comps = i.prepare_computations(r);
  Color c = w.shade_hit(comps);
  CHECK(nearly_equal(c, Color(0.1, 0.1, 0.1)));
}

#if 0
TEST_CASE("The reflected color for a non-reflective material", "[world]")
{
  auto w = default_world();
  auto r = ray(point(0, 0, 0), vector(0, 0, 1));
  auto shape = the second object in w;
  auto shape.material.ambient = 1;
  auto i = intersection(1, shape);
  auto comps = prepare_computations(i, r);
  auto color = reflected_color(w, comps);
  CHECK(color == color(0, 0, 0));
}

TEST_CASE("The reflected color for a reflective material", "[world]")
{
  auto w = default_world();
  auto shape = plane() with:;
  shape is added to w
  auto r = ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2));
  auto i = intersection(sqrt(2), shape);
  auto comps = prepare_computations(i, r);
  auto color = reflected_color(w, comps);
  CHECK(color == color(0.19032, 0.2379, 0.14274));
}

TEST_CASE("shade_hit() with a reflective material", "[world]")
{
  auto w = default_world();
  auto shape = plane() with:;
  shape is added to w
  auto r = ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2));
  auto i = intersection(sqrt(2), shape);
  auto comps = prepare_computations(i, r);
  auto color = shade_hit(w, comps);
  CHECK(color == color(0.87677, 0.92436, 0.82918));
}

TEST_CASE("color_at() with mutually reflective surfaces", "[world]")
{
  auto w = world();
  auto w.light = point_light(point(0, 0, 0), color(1, 1, 1));
  auto lower = plane() with:;
  lower is added to w
  auto upper = plane() with:;
  upper is added to w
  auto r = ray(point(0, 0, 0), vector(0, 1, 0));
  color_at(w, r) should terminate successfully;
}

TEST_CASE("The reflected color at the maximum recursive depth", "[world]")
{
  auto w = default_world();
  auto shape = plane() with:;
  shape is added to w
  auto r = ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2));
  auto i = intersection(sqrt(2), shape);
  auto comps = prepare_computations(i, r);
  auto color = reflected_color(w, comps, 0);
  CHECK(color == color(0, 0, 0));
}

TEST_CASE("The refracted color with an opaque surface", "[world]")
{
  auto w = default_world();
  auto shape = the first object in w;
  auto r = ray(point(0, 0, -5), vector(0, 0, 1));
  Intersections xs = {{4, shape}, {6, shape}};
  auto comps = prepare_computations(xs[0], r, xs);
  auto c = refracted_color(w, comps, 5);
  CHECK(c == color(0, 0, 0));
}

TEST_CASE("The refracted color at the maximum recursive depth", "[world]")
{
  auto w = default_world();
  auto shape = the first object in w;
  shape has = {
    {material.transparency, 1.0},
    {material.refractive_index, 1.5}
  };
  auto r = ray(point(0, 0, -5), vector(0, 0, 1));
  Intersections xs = {{4, shape}, {6, shape}};
  auto comps = prepare_computations(xs[0], r, xs);
  auto c = refracted_color(w, comps, 0);
  CHECK(c == color(0, 0, 0));
}

TEST_CASE("The refracted color under total internal reflection", "[world]")
{
  auto w = default_world();
  auto shape = the first object in w;
  shape has = {
    {material.transparency, 1.0},
    {material.refractive_index, 1.5}
  };
  auto r = ray(point(0, 0, sqrt(2)/2), vector(0, 1, 0));
  Intersections xs = {{-sqrt(2)/2, shape}, {sqrt(2)/2, shape}};
  auto comps = prepare_computations(xs[1], r, xs);
  auto c = refracted_color(w, comps, 5);
  CHECK(c == color(0, 0, 0));
}

TEST_CASE("The refracted color with a refracted ray", "[world]")
{
  auto w = default_world();
  auto A = the first object in w;
  A has = {
    {material.ambient, 1.0},
    {material.pattern, test_pattern()}
  };
  auto B = the second object in w;
  B has = {
    {material.transparency, 1.0},
    {material.refractive_index, 1.5}
  };
  auto r = ray(point(0, 0, 0.1), vector(0, 1, 0));
  Intersections xs = {{-0.9899, A}, {-0.4899, B}, {0.4899, B}, {0.9899, A}};
  auto comps = prepare_computations(xs[2], r, xs);
  auto c = refracted_color(w, comps, 5);
  CHECK(c == color(0, 0.99888, 0.04725));
}

TEST_CASE("shade_hit() with a transparent material", "[world]")
{
  auto w = default_world();
  auto floor = plane() with:;
  floor is added to w
  auto ball = sphere() with:;
  ball is added to w
  auto r = ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2));
  Intersections xs = {{sqrt(2), floor}};
  auto comps = prepare_computations(xs[0], r, xs);
  auto color = shade_hit(w, comps, 5);
  CHECK(color == color(0.93642, 0.68642, 0.68642));
}

TEST_CASE("shade_hit() with a reflective, transparent material", "[world]")
{
  auto w = default_world();
  auto r = ray(point(0, 0, -3), vector(0, -sqrt(2)/2, sqrt(2)/2));
  auto floor = plane() with:;
  floor is added to w
  auto ball = sphere() with:;
  ball is added to w
  Intersections xs = {{sqrt(2), floor}};
  auto comps = prepare_computations(xs[0], r, xs);
  auto color = shade_hit(w, comps, 5);
  CHECK(color == color(0.93391, 0.69643, 0.69243));
}
#endif
