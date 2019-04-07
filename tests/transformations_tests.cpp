#include <catch2/catch.hpp>

#include <raytracer/matrix.h>
#include <raytracer/transform.h>

TEST_CASE("Multiplying by a translation matrix", "[transformations]")
{
  Matrix transform = translation(5, -3, 2);
  Tuple p = point(-3, 4, 5);
  CHECK(transform * p == point(2, 1, 7));
}

TEST_CASE("Multiplying by the inverse of a translation matrix", "[transformations]")
{
  Matrix transform = translation(5, -3, 2);
  Matrix inv = transform.inverse();
  Tuple p = point(-3, 4, 5);
  CHECK(inv * p == point(-8, 7, 3));
}

TEST_CASE("translation does not affect vectors", "[transformations]")
{
  Matrix transform = translation(5, -3, 2);
  Tuple v = vector(-3, 4, 5);
  CHECK(transform * v == v);
}

TEST_CASE("A scaling matrix applied to a point", "[transformations]")
{
  Matrix transform = scaling(2, 3, 4);
  Tuple p = point(-4, 6, 8);
  CHECK(transform * p == point(-8, 18, 32));
}

TEST_CASE("A scaling matrix applied to a vector", "[transformations]")
{
  Matrix transform = scaling(2, 3, 4);
  Tuple v = vector(-4, 6, 8);
  CHECK(transform * v == vector(-8, 18, 32));
}

TEST_CASE("Multiplying by the inverse of a scaling matrix", "[transformations]")
{
  Matrix transform = scaling(2, 3, 4);
  Matrix inv = transform.inverse();
  Tuple v = vector(-4, 6, 8);
  CHECK(inv * v == vector(-2, 2, 2));
}

TEST_CASE("Reflection is scaling by a negative value", "[transformations]")
{
  Matrix transform = scaling(-1, 1, 1);
  Tuple p = point(2, 3, 4);
  CHECK(transform * p == point(-2, 3, 4));
}

TEST_CASE("Rotating a point around the x axis", "[transformations]")
{
  Tuple p = point(0, 1, 0);
  Matrix half_quarter = rotation_x(M_PI / 4);
  Matrix full_quarter = rotation_x(M_PI / 2);
  CHECK(nearly_equal(half_quarter * p, point(0, sqrt(2)/2, sqrt(2)/2)));
  CHECK(nearly_equal(full_quarter * p, point(0, 0, 1)));
}

TEST_CASE("The inverse of an x-rotation rotates in the opposite direction", "[transformations]")
{
  Tuple p = point(0, 1, 0);
  Matrix half_quarter = rotation_x(M_PI / 4);
  Matrix inv = half_quarter.inverse();
  CHECK(nearly_equal(inv * p, point(0, sqrt(2)/2, -sqrt(2)/2)));
}

TEST_CASE("Rotating a point around the y axis", "[transformations]")
{
  Tuple p = point(0, 0, 1);
  Matrix half_quarter = rotation_y(M_PI / 4);
  Matrix full_quarter = rotation_y(M_PI / 2);
  CHECK(nearly_equal(half_quarter * p, point(sqrt(2)/2, 0, sqrt(2)/2)));
  CHECK(nearly_equal(full_quarter * p, point(1, 0, 0)));
}

TEST_CASE("Rotating a point around thezaxis", "[transformations]")
{
  Tuple p = point(0, 1, 0);
  Matrix half_quarter = rotation_z(M_PI / 4);
  Matrix full_quarter = rotation_z(M_PI / 2);
  CHECK(nearly_equal(half_quarter * p, point(-sqrt(2)/2, sqrt(2)/2, 0)));
  CHECK(nearly_equal(full_quarter * p, point(-1, 0, 0)));
}

TEST_CASE("A shearing transformation moves x in proportion to y", "[transformations]")
{
  Matrix transform = shearing(1, 0, 0, 0, 0, 0);
  Tuple p = point(2, 3, 4);
  CHECK(transform * p == point(5, 3, 4));
}

TEST_CASE("A shearing transformation moves x in proportion to z", "[transformations]")
{
  Matrix transform = shearing(0, 1, 0, 0, 0, 0);
  Tuple p = point(2, 3, 4);
  CHECK(transform * p == point(6, 3, 4));
}

TEST_CASE("A shearing transformation moves y in proportion to x", "[transformations]")
{
  Matrix transform = shearing(0, 0, 1, 0, 0, 0);
  Tuple p = point(2, 3, 4);
  CHECK(transform * p == point(2, 5, 4));
}

TEST_CASE("A shearing transformation moves y in proportion to z", "[transformations]")
{
  Matrix transform = shearing(0, 0, 0, 1, 0, 0);
  Tuple p = point(2, 3, 4);
  CHECK(transform * p == point(2, 7, 4));
}

TEST_CASE("A shearing transformation moveszin proportion to x", "[transformations]")
{
  Matrix transform = shearing(0, 0, 0, 0, 1, 0);
  Tuple p = point(2, 3, 4);
  CHECK(transform * p == point(2, 3, 6));
}

TEST_CASE("A shearing transformation moveszin proportion to y", "[transformations]")
{
  Matrix transform = shearing(0, 0, 0, 0, 0, 1);
  Tuple p = point(2, 3, 4);
  CHECK(transform * p == point(2, 3, 7));
}

TEST_CASE("Individual transformations are applied in sequence", "[transformations]")
{
  Tuple p = point(1, 0, 1);
  Matrix A = rotation_x(M_PI / 2);
  Matrix B = scaling(5, 5, 5);
  Matrix C = translation(10, 5, 7);
  Tuple p2 = A * p;
  CHECK(nearly_equal(p2, point(1, -1, 0)));
  Tuple p3 = B * p2;
  CHECK(nearly_equal(p3, point(5, -5, 0)));
  Tuple p4 = C * p3;
  CHECK(p4 == point(15, 0, 7));
}

TEST_CASE("Chained transformations must be applied in reverse order", "[transformations]")
{
  Tuple p = point(1, 0, 1);
  Matrix A = rotation_x(M_PI / 2);
  Matrix B = scaling(5, 5, 5);
  Matrix C = translation(10, 5, 7);
  CHECK(C * B * A * p == point(15, 0, 7));
}

TEST_CASE("The transformation matrix for the default orientation", "[transformations]")
{
  Tuple from = point(0, 0, 0);
  Tuple to = point(0, 0, -1);
  Tuple up = vector(0, 1, 0);
  Matrix t = view_transform(from, to, up);
  CHECK(t == Matrix::identity_matrix());
}

TEST_CASE("A view transformation matrix looking in positivezdirection", "[transformations]")
{
  Tuple from = point(0, 0, 0);
  Tuple to = point(0, 0, 1);
  Tuple up = vector(0, 1, 0);
  Matrix t = view_transform(from, to, up);
  CHECK(t == scaling(-1, 1, -1));
}

TEST_CASE("The view transformation moves the world", "[transformations]")
{
  Tuple from = point(0, 0, 8);
  Tuple to = point(0, 0, 0);
  Tuple up = vector(0, 1, 0);
  Matrix t = view_transform(from, to, up);
  CHECK(t == translation(0, 0, -8));
}

TEST_CASE("An arbitrary view transformation", "[transformations]")
{
  Tuple from = point(1, 3, 2);
  Tuple to = point(4, -2, 8);
  Tuple up = vector(1, 1, 0);
  Matrix t = view_transform(from, to, up);
  Matrix expected = {
    {-0.50709, 0.50709, 0.67612, -2.36643},
    {0.76772, 0.60609, 0.12122, -2.82843},
    {-0.35857, 0.59761, -0.71714, 0.00000},
    {0.00000, 0.00000, 0.00000, 1.00000}
  };
  CHECK(t.approximately_equal(expected));
}
