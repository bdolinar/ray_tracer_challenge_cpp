#include <catch2/catch.hpp>

#include <raytracer/light.h>
#include <raytracer/material.h>


TEST_CASE("The default material", "[materials]")
{
  Material m;
  CHECK(m.color() == Color(1, 1, 1));
  CHECK(m.ambient() == 0.1);
  CHECK(m.diffuse() == 0.9);
  CHECK(m.specular() == 0.9);
  CHECK(m.shininess() == 200.0);
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

TEST_CASE("lighting with the eye between the light and the surface", "[materials]")
{
  Material m;
  Tuple position = point(0, 0, 0);
  Tuple eyev = vector(0, 0, -1);
  Tuple normalv = vector(0, 0, -1);
  Light light(point(0, 0, -10), Color(1, 1, 1));
  bool in_shadow = false;
  Color result = lighting(m, light, position, eyev, normalv, in_shadow);
  CHECK(result == Color(1.9, 1.9, 1.9));
}

TEST_CASE("lighting with the eye between light and surface, eye offset 45°", "[materials]")
{
  Material m;
  Tuple position = point(0, 0, 0);
  Tuple eyev = vector(0, sqrt(2)/2, -sqrt(2)/2);
  Tuple normalv = vector(0, 0, -1);
  Light light(point(0, 0, -10), Color(1, 1, 1));
  bool in_shadow = false;
  Color result = lighting(m, light, position, eyev, normalv, in_shadow);
  CHECK(result == Color(1.0, 1.0, 1.0));
}

TEST_CASE("lighting with eye opposite surface, light offset 45°", "[materials]")
{
  Material m;
  Tuple position = point(0, 0, 0);
  Tuple eyev = vector(0, 0, -1);
  Tuple normalv = vector(0, 0, -1);
  Light light(point(0, 10, -10), Color(1, 1, 1));
  bool in_shadow = false;
  Color result = lighting(m, light, position, eyev, normalv, in_shadow);
  CHECK(approximately_equal(result, Color(0.7364, 0.7364, 0.7364)));
}

TEST_CASE("lighting with eye in the path of the reflection vector", "[materials]")
{
  Material m;
  Tuple position = point(0, 0, 0);
  Tuple eyev = vector(0, -sqrt(2)/2, -sqrt(2)/2);
  Tuple normalv = vector(0, 0, -1);
  Light light(point(0, 10, -10), Color(1, 1, 1));
  bool in_shadow = false;
  Color result = lighting(m, light, position, eyev, normalv, in_shadow);
  CHECK(approximately_equal(result, Color(1.6364, 1.6364, 1.6364)));
}

TEST_CASE("lighting with the light behind the surface", "[materials]")
{
  Material m;
  Tuple position = point(0, 0, 0);
  Tuple eyev = vector(0, 0, -1);
  Tuple normalv = vector(0, 0, -1);
  Light light(point(0, 0, 10), Color(1, 1, 1));
  bool in_shadow = false;
  Color result = lighting(m, light, position, eyev, normalv, in_shadow);
  CHECK(result == Color(0.1, 0.1, 0.1));
}

TEST_CASE("Lighting with the surface in shadow", "[materials]")
{
  Material m;
  Tuple position = point(0, 0, 0);
  Tuple eyev = vector(0, 0, -1);
  Tuple normalv = vector(0, 0, -1);
  Light light(point(0, 0, -10), Color(1, 1, 1));
  bool in_shadow = true;
  Color result = lighting(m, light, position, eyev, normalv, in_shadow);
  CHECK(nearly_equal(result, Color(0.1, 0.1, 0.1)));
}

#if 0
TEST_CASE("Lighting with a pattern applied", "[materials]")
{
  auto m.pattern = stripe_pattern(Color(1, 1, 1), Color(0, 0, 0));
  auto m.ambient = 1;
  auto m.diffuse = 0;
  auto m.specular = 0;
  Tuple eyev = vector(0, 0, -1);
  Tuple normalv = vector(0, 0, -1);
  Light light(point(0, 0, -10), Color(1, 1, 1));
  auto c1 = Lighting(m, light, point(0.9, 0, 0), eyev, normalv, false);
  auto c2 = Lighting(m, light, point(1.1, 0, 0), eyev, normalv, false);
  CHECK(c1 == Color(1, 1, 1));
  CHECK(c2 == Color(0, 0, 0));
}
#endif
