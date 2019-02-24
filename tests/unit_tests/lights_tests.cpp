#include <catch2/catch.hpp>

#include "color.h"
#include "light.h"
#include "tuple.h"

TEST_CASE("A point light has a position and intensity", "[lights]")
{
  Color intensity(1, 1, 1);
  Tuple position = Point(0, 0, 0);
  Light light(position, intensity);
  CHECK(light.Position() == position);
  CHECK(light.Intensity() == intensity);
}
