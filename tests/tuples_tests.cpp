#include <cmath>

#include <catch2/catch.hpp>

#include <raytracer/color.h>
#include <raytracer/tuple.h>


TEST_CASE("A tuple with w=1.0 is a point", "[tuples]")
{
  Tuple a = Tuple(4.3, -4.2, 3.1, 1.0);
  CHECK(a.x == 4.3);
  CHECK(a.y == -4.2);
  CHECK(a.z == 3.1);
  CHECK(a.w == 1.0);
  CHECK(a.IsPoint());
  CHECK_FALSE(a.IsVector());
}

TEST_CASE("A tuple with w=0 is a vector", "[tuples]")
{
  Tuple a(4.3, -4.2, 3.1, 0.0);
  CHECK(a.x == 4.3);
  CHECK(a.y == -4.2);
  CHECK(a.z == 3.1);
  CHECK(a.w == 0.0);
  CHECK_FALSE(a.IsPoint());
  CHECK(a.IsVector());
}

TEST_CASE("point() creates tuples with w=1", "[tuples]")
{
  Tuple p = Point(4, -4, 3);
  CHECK(p == Tuple(4, -4, 3, 1));
}

TEST_CASE("vector() creates tuples with w=0", "[tuples]")
{
  Tuple v = Vector(4, -4, 3);
  CHECK(v == Tuple(4, -4, 3, 0));
}

TEST_CASE("Adding two tuples", "[tuples]")
{
  Tuple a1(3, -2, 5, 1);
  Tuple a2(-2, 3, 1, 0);
  CHECK(a1 + a2 == Tuple(1, 1, 6, 1));
}

TEST_CASE("Subtracting two points", "[tuples]")
{
  Tuple p1 = Point(3, 2, 1);
  Tuple p2 = Point(5, 6, 7);
  CHECK(p1 - p2 == Vector(-2, -4, -6));
}

TEST_CASE("Subtracting a vector from a point", "[tuples]")
{
  Tuple p = Point(3, 2, 1);
  Tuple v = Vector(5, 6, 7);
  CHECK(p - v == Point(-2, -4, -6));
}

TEST_CASE("Subtracting two vectors", "[tuples]")
{
  Tuple v1 = Vector(3, 2, 1);
  Tuple v2 = Vector(5, 6, 7);
  CHECK(v1 - v2 == Vector(-2, -4, -6));
}

TEST_CASE("Subtracting a vector from the zero vector", "[tuples]")
{
  Tuple zero = Vector(0, 0, 0);
  Tuple v = Vector(1, -2, 3);
  CHECK(zero - v == Vector(-1, 2, -3));
}

TEST_CASE("Negating a tuple", "[tuples]")
{
  Tuple a(1, -2, 3, -4);
  CHECK(-a == Tuple(-1, 2, -3, 4));
}

TEST_CASE("Multiplying a tuple by a scalar", "[tuples]")
{
  Tuple a(1, -2, 3, -4);
  CHECK(a * 3.5 == Tuple(3.5, -7, 10.5, -14));
}

TEST_CASE("Multiplying a tuple by a fraction", "[tuples]")
{
  Tuple a(1, -2, 3, -4);
  CHECK(a * 0.5 == Tuple(0.5, -1, 1.5, -2));
}

TEST_CASE("Dividing a tuple by a scalar", "[tuples]")
{
  Tuple a(1, -2, 3, -4);
  CHECK(a / 2 == Tuple(0.5, -1, 1.5, -2));
}

TEST_CASE("Computing the magnitude of vector(1, 0, 0)", "[tuples]")
{
  Tuple v = Vector(1, 0, 0);
  CHECK(v.Magnitude() == 1);
}

TEST_CASE("Computing the magnitude of vector(0, 1, 0)", "[tuples]")
{
  Tuple v = Vector(0, 1, 0);
  CHECK(v.Magnitude() == 1);
}

TEST_CASE("Computing the magnitude of vector(0, 0, 1)", "[tuples]")
{
  Tuple v = Vector(0, 0, 1);
  CHECK(v.Magnitude() == 1);
}

TEST_CASE("Computing the magnitude of vector(1, 2, 3)", "[tuples]")
{
  Tuple v = Vector(1, 2, 3);
  CHECK(v.Magnitude() == sqrt(14));
}

TEST_CASE("Computing the magnitude of vector(-1, -2, -3)", "[tuples]")
{
  Tuple v = Vector(-1, -2, -3);
  CHECK(v.Magnitude() == sqrt(14));
}

TEST_CASE("Normalizing vector(4, 0, 0) gives (1, 0, 0)", "[tuples]")
{
  Tuple v = Vector(4, 0, 0);
  CHECK(v.Normalize() == Vector(1, 0, 0));
}

TEST_CASE("Normalizing vector(1, 2, 3)", "[tuples]")
{
  Tuple v = Vector(1, 2, 3);
  CHECK(ApproximatelyEqual(v.Normalize(), Vector(0.26726, 0.53452, 0.80178)));
}

TEST_CASE("The magnitude of a normalized vector", "[tuples]")
{
  Tuple v = Vector(1, 2, 3);
  Tuple norm = v.Normalize();
  CHECK(norm.Magnitude() == 1);
}

TEST_CASE("The dot product of two tuples", "[tuples]")
{
  Tuple a = Vector(1, 2, 3);
  Tuple b = Vector(2, 3, 4);
  CHECK(Dot(a, b) == 20);
}

TEST_CASE("The cross product of two vectors", "[tuples]")
{
  Tuple a = Vector(1, 2, 3);
  Tuple b = Vector(2, 3, 4);
  CHECK(Cross(a, b) == Vector(-1, 2, -1));
  CHECK(Cross(b, a) == Vector(1, -2, 1));
}

TEST_CASE("Colors are (red, green, blue) tuples", "[tuples]")
{
  Color c(-0.5, 0.4, 1.7);
  CHECK(c.Red() == -0.5);
  CHECK(c.Green() == 0.4);
  CHECK(c.Blue() == 1.7);
}

TEST_CASE("Adding colors", "[tuples]")
{
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);
  CHECK(c1 + c2 == Color(1.6, 0.7, 1.0));
}

TEST_CASE("Subtracting colors", "[tuples]")
{
  Color c1(0.9, 0.6, 0.75);
  Color c2(0.7, 0.1, 0.25);
  CHECK(NearlyEqual(c1 - c2, Color(0.2, 0.5, 0.5)));
}

TEST_CASE("Multiplying a color by a scalar", "[tuples]")
{
  Color c(0.2, 0.3, 0.4);
  CHECK(c * 2 == Color(0.4, 0.6, 0.8));
}

TEST_CASE("Multiplying colors", "[tuples]")
{
  Color c1(1, 0.2, 0.4);
  Color c2(0.9, 1, 0.1);
  CHECK(NearlyEqual(c1 * c2, Color(0.9, 0.2, 0.04)));
}

TEST_CASE("Reflecting a vector approaching at 45°", "[tuples]")
{
  Tuple v = Vector(1, -1, 0);
  Tuple n = Vector(0, 1, 0);
  Tuple r = Reflect(v, n);
  CHECK(r == Vector(1, 1, 0));
}

TEST_CASE("Reflecting a vector off a slanted surface", "[tuples]")
{
  Tuple v = Vector(0, -1, 0);
  Tuple n = Vector(sqrt(2)/2, sqrt(2)/2, 0);
  Tuple r = Reflect(v, n);
  CHECK(NearlyEqual(r, Vector(1, 0, 0)));
}
