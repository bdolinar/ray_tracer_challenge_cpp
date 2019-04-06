#include <catch2/catch.hpp>

#include "matrix.h"
#include "transform.h"

TEST_CASE("Multiplying by a translation matrix", "[transformations]")
{
  Matrix transform = Translation(5, -3, 2);
  Tuple p = Point(-3, 4, 5);
  CHECK(transform * p == Point(2, 1, 7));
}

TEST_CASE("Multiplying by the inverse of a translation matrix", "[transformations]")
{
  Matrix transform = Translation(5, -3, 2);
  Matrix inv = transform.Inverse();
  Tuple p = Point(-3, 4, 5);
  CHECK(inv * p == Point(-8, 7, 3));
}

TEST_CASE("Translation does not affect vectors", "[transformations]")
{
  Matrix transform = Translation(5, -3, 2);
  Tuple v = Vector(-3, 4, 5);
  CHECK(transform * v == v);
}

TEST_CASE("A scaling matrix applied to a point", "[transformations]")
{
  Matrix transform = Scaling(2, 3, 4);
  Tuple p = Point(-4, 6, 8);
  CHECK(transform * p == Point(-8, 18, 32));
}

TEST_CASE("A scaling matrix applied to a vector", "[transformations]")
{
  Matrix transform = Scaling(2, 3, 4);
  Tuple v = Vector(-4, 6, 8);
  CHECK(transform * v == Vector(-8, 18, 32));
}

TEST_CASE("Multiplying by the inverse of a scaling matrix", "[transformations]")
{
  Matrix transform = Scaling(2, 3, 4);
  Matrix inv = transform.Inverse();
  Tuple v = Vector(-4, 6, 8);
  CHECK(inv * v == Vector(-2, 2, 2));
}

TEST_CASE("Reflection is scaling by a negative value", "[transformations]")
{
  Matrix transform = Scaling(-1, 1, 1);
  Tuple p = Point(2, 3, 4);
  CHECK(transform * p == Point(-2, 3, 4));
}

TEST_CASE("Rotating a point around the x axis", "[transformations]")
{
  Tuple p = Point(0, 1, 0);
  Matrix half_quarter = RotationX(M_PI / 4);
  Matrix full_quarter = RotationX(M_PI / 2);
  CHECK(half_quarter * p == Point(0, sqrt(2)/2, sqrt(2)/2));
  CHECK(full_quarter * p == Point(0, 0, 1));
}

TEST_CASE("The inverse of an x-rotation rotates in the opposite direction", "[transformations]")
{
  Tuple p = Point(0, 1, 0);
  Matrix half_quarter = RotationX(M_PI / 4);
  Matrix inv = half_quarter.Inverse();
  CHECK(inv * p == Point(0, sqrt(2)/2, -sqrt(2)/2));
}

TEST_CASE("Rotating a point around the y axis", "[transformations]")
{
  Tuple p = Point(0, 0, 1);
  Matrix half_quarter = RotationY(M_PI / 4);
  Matrix full_quarter = RotationY(M_PI / 2);
  CHECK(half_quarter * p == Point(sqrt(2)/2, 0, sqrt(2)/2));
  CHECK(full_quarter * p == Point(1, 0, 0));
}

TEST_CASE("Rotating a point around the z axis", "[transformations]")
{
  Tuple p = Point(0, 1, 0);
  Matrix half_quarter = RotationZ(M_PI / 4);
  Matrix full_quarter = RotationZ(M_PI / 2);
  CHECK(half_quarter * p == Point(-sqrt(2)/2, sqrt(2)/2, 0));
  CHECK(full_quarter * p == Point(-1, 0, 0));
}

TEST_CASE("A shearing transformation moves x in proportion to y", "[transformations]")
{
  Matrix transform = Shearing(1, 0, 0, 0, 0, 0);
  Tuple p = Point(2, 3, 4);
  CHECK(transform * p == Point(5, 3, 4));
}

TEST_CASE("A shearing transformation moves x in proportion to z", "[transformations]")
{
  Matrix transform = Shearing(0, 1, 0, 0, 0, 0);
  Tuple p = Point(2, 3, 4);
  CHECK(transform * p == Point(6, 3, 4));
}

TEST_CASE("A shearing transformation moves y in proportion to x", "[transformations]")
{
  Matrix transform = Shearing(0, 0, 1, 0, 0, 0);
  Tuple p = Point(2, 3, 4);
  CHECK(transform * p == Point(2, 5, 4));
}

TEST_CASE("A shearing transformation moves y in proportion to z", "[transformations]")
{
  Matrix transform = Shearing(0, 0, 0, 1, 0, 0);
  Tuple p = Point(2, 3, 4);
  CHECK(transform * p == Point(2, 7, 4));
}

TEST_CASE("A shearing transformation moves z in proportion to x", "[transformations]")
{
  Matrix transform = Shearing(0, 0, 0, 0, 1, 0);
  Tuple p = Point(2, 3, 4);
  CHECK(transform * p == Point(2, 3, 6));
}

TEST_CASE("A shearing transformation moves z in proportion to y", "[transformations]")
{
  Matrix transform = Shearing(0, 0, 0, 0, 0, 1);
  Tuple p = Point(2, 3, 4);
  CHECK(transform * p == Point(2, 3, 7));
}

TEST_CASE("Individual transformations are applied in sequence", "[transformations]")
{
  Tuple p = Point(1, 0, 1);
  Matrix A = RotationX(M_PI / 2);
  Matrix B = Scaling(5, 5, 5);
  Matrix C = Translation(10, 5, 7);
  Tuple p2 = A * p;
  CHECK(p2 == Point(1, -1, 0));
  Tuple p3 = B * p2;
  CHECK(p3 == Point(5, -5, 0));
  Tuple p4 = C * p3;
  CHECK(p4 == Point(15, 0, 7));
}

TEST_CASE("Chained transformations must be applied in reverse order", "[transformations]")
{
  Tuple p = Point(1, 0, 1);
  Matrix A = RotationX(M_PI / 2);
  Matrix B = Scaling(5, 5, 5);
  Matrix C = Translation(10, 5, 7);
  CHECK(C * B * A * p == Point(15, 0, 7));
}

#if 0
TEST_CASE("The transformation matrix for the default orientation", "[transformations]")
{
  Tuple from = Point(0, 0, 0);
  Tuple to = Point(0, 0, -1);
  Tuple up = Vector(0, 1, 0);
  auto t = view_transform(from, to, up);
  CHECK(t == identity_matrix);
}

TEST_CASE("A view transformation matrix looking in positive z direction", "[transformations]")
{
  Tuple from = Point(0, 0, 0);
  Tuple to = Point(0, 0, 1);
  Tuple up = Vector(0, 1, 0);
  auto t = view_transform(from, to, up);
  CHECK(t == scaling(-1, 1, -1));
}

TEST_CASE("The view transformation moves the world", "[transformations]")
{
  Tuple from = Point(0, 0, 8);
  Tuple to = Point(0, 0, 0);
  Tuple up = Vector(0, 1, 0);
  auto t = view_transform(from, to, up);
  CHECK(t == translation(0, 0, -8));
}

TEST_CASE("An arbitrary view transformation", "[transformations]")
{
  Tuple from = Point(1, 3, 2);
  Tuple to = Point(4, -2, 8);
  Tuple up = Vector(1, 1, 0);
  auto t = view_transform(from, to, up);
  Matrix4 expected = {
    {-0.50709, 0.50709, 0.67612, -2.36643},
    {0.76772, 0.60609, 0.12122, -2.82843},
    {-0.35857, 0.59761, -0.71714, 0.00000},
    {0.00000, 0.00000, 0.00000, 1.00000}
  };
  CHECK(t == expected);
}
#endif
