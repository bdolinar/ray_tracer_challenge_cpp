#include <catch2/catch.hpp>

#include <raytracer/light.h>
#include <raytracer/material.h>


TEST_CASE("The default material", "[materials]")
{
  Material m;
  CHECK(m.Color() == Color(1, 1, 1));
  CHECK(m.Ambient() == 0.1);
  CHECK(m.Diffuse() == 0.9);
  CHECK(m.Specular() == 0.9);
  CHECK(m.Shininess() == 200.0);
}

#if 0
TEST_CASE("Reflectivity for the default material", "[materials]")
{
  Material m;
  CHECK(m.reflective == 0.0);
}

TEST_CASE("Transparency and Refractive Index for the default material", "[materials]")
{
  Material m;
  CHECK(m.transparency == 0.0);
  CHECK(m.refractive_index == 1.0);
}
#endif

TEST_CASE("Lighting with the eye between the light and the surface", "[materials]")
{
  Material m;
  Tuple position = Point(0, 0, 0);
  Tuple eyev = Vector(0, 0, -1);
  Tuple normalv = Vector(0, 0, -1);
  Light light(Point(0, 0, -10), Color(1, 1, 1));
  Color result = Lighting(m, light, position, eyev, normalv);
  CHECK(result == Color(1.9, 1.9, 1.9));
}

TEST_CASE("Lighting with the eye between light and surface, eye offset 45°", "[materials]")
{
  Material m;
  Tuple position = Point(0, 0, 0);
  Tuple eyev = Vector(0, sqrt(2)/2, -sqrt(2)/2);
  Tuple normalv = Vector(0, 0, -1);
  Light light(Point(0, 0, -10), Color(1, 1, 1));
  Color result = Lighting(m, light, position, eyev, normalv);
  CHECK(result == Color(1.0, 1.0, 1.0));
}

TEST_CASE("Lighting with eye opposite surface, light offset 45°", "[materials]")
{
  Material m;
  Tuple position = Point(0, 0, 0);
  Tuple eyev = Vector(0, 0, -1);
  Tuple normalv = Vector(0, 0, -1);
  Light light(Point(0, 10, -10), Color(1, 1, 1));
  Color result = Lighting(m, light, position, eyev, normalv);
  CHECK(ApproximatelyEqual(result, Color(0.7364, 0.7364, 0.7364)));
}

TEST_CASE("Lighting with eye in the path of the reflection vector", "[materials]")
{
  Material m;
  Tuple position = Point(0, 0, 0);
  Tuple eyev = Vector(0, -sqrt(2)/2, -sqrt(2)/2);
  Tuple normalv = Vector(0, 0, -1);
  Light light(Point(0, 10, -10), Color(1, 1, 1));
  Color result = Lighting(m, light, position, eyev, normalv);
  CHECK(ApproximatelyEqual(result, Color(1.6364, 1.6364, 1.6364)));
}

TEST_CASE("Lighting with the light behind the surface", "[materials]")
{
  Material m;
  Tuple position = Point(0, 0, 0);
  Tuple eyev = Vector(0, 0, -1);
  Tuple normalv = Vector(0, 0, -1);
  Light light(Point(0, 0, 10), Color(1, 1, 1));
  Color result = Lighting(m, light, position, eyev, normalv);
  CHECK(result == Color(0.1, 0.1, 0.1));
}

#if 0
TEST_CASE("Lighting with the surface in shadow", "[materials]")
{
  Tuple eyev = Vector(0, 0, -1);
  Tuple normalv = Vector(0, 0, -1);
  Light light(Point(0, 0, -10), Color(1, 1, 1));
  auto in_shadow = true;
  Color result = Lighting(m, light, position, eyev, normalv, in_shadow);
  CHECK(result == Color(0.1, 0.1, 0.1));
}

TEST_CASE("Lighting with a pattern applied", "[materials]")
{
  auto m.pattern = stripe_pattern(Color(1, 1, 1), Color(0, 0, 0));
  auto m.ambient = 1;
  auto m.diffuse = 0;
  auto m.specular = 0;
  Tuple eyev = Vector(0, 0, -1);
  Tuple normalv = Vector(0, 0, -1);
  Light light(Point(0, 0, -10), Color(1, 1, 1));
  auto c1 = Lighting(m, light, Point(0.9, 0, 0), eyev, normalv, false);
  auto c2 = Lighting(m, light, Point(1.1, 0, 0), eyev, normalv, false);
  CHECK(c1 == Color(1, 1, 1));
  CHECK(c2 == Color(0, 0, 0));
}
#endif
