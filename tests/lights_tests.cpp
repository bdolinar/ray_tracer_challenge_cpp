#include <catch2/catch.hpp>

#include <raytracer/color.h>
#include <raytracer/light.h>

TEST_CASE("A point light has a position and intensity", "[lights]")
{
  Color intensity(1, 1, 1);
  Tuple position = point(0, 0, 0);
  Light light(position, intensity);
  CHECK(light.position() == position);
  CHECK(light.intensity() == intensity);
}
