#include <catch2/catch.hpp>

#include <raytracer/matrix.h>

TEST_CASE("Constructing and inspecting a 4x4 matrix", "[matrices]")
{
  Matrix M = {
    {1, 2, 3, 4},
    {5.5, 6.5, 7.5, 8.5},
    {9, 10, 11, 12},
    {13.5, 14.5, 15.5, 16.5}
  };
  CHECK(M[0][0] == 1);
  CHECK(M[0][3] == 4);
  CHECK(M[1][0] == 5.5);
  CHECK(M[1][2] == 7.5);
  CHECK(M[2][2] == 11);
  CHECK(M[3][0] == 13.5);
  CHECK(M[3][2] == 15.5);
}

TEST_CASE("A 2x2 matrix ought to be representable", "[matrices]")
{
  Matrix M = {
    {-3, 5},
    {1, -2}
  };
  CHECK(M[0][0] == -3);
  CHECK(M[0][1] == 5);
  CHECK(M[1][0] == 1);
  CHECK(M[1][1] == -2);
}

TEST_CASE("A 3x3 matrix ought to be representable", "[matrices]")
{
  Matrix M = {
    {-3, 5, 0},
    {1, -2, -7},
    {0, 1, 1}
  };
  CHECK(M[0][0] == -3);
  CHECK(M[1][1] == -2);
  CHECK(M[2][2] == 1);
}

TEST_CASE("Matrix equality with identical matrices", "[matrices]")
{
  Matrix A = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 8, 7, 6},
    {5, 4, 3, 2}
  };
  Matrix B = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 8, 7, 6},
    {5, 4, 3, 2}
  };
  CHECK(A == B);
}

TEST_CASE("Matrix equality with different matrices", "[matrices]")
{
  Matrix A = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 8, 7, 6},
    {5, 4, 3, 2}
  };
  Matrix B = {
    {2, 3, 4, 5},
    {6, 7, 8, 9},
    {8, 7, 6, 5},
    {4, 3, 2, 1}
  };
  CHECK(A != B);
}

TEST_CASE("Multiplying two matrices", "[matrices]")
{
  Matrix A = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 8, 7, 6},
    {5, 4, 3, 2}
  };
  Matrix B = {
    {-2, 1, 2, 3},
    {3, 2, 1, -1},
    {4, 3, 6, 5},
    {1, 2, 7, 8}
  };
  Matrix expected = {
    {20, 22, 50, 48},
    {44, 54, 114, 108},
    {40, 58, 110, 102},
    {16, 26, 46, 42}
  };
  CHECK(A * B == expected);
}

TEST_CASE("A matrix multiplied by a tuple", "[matrices]")
{
  Matrix A = {
    {1, 2, 3, 4},
    {2, 4, 4, 2},
    {8, 6, 4, 1},
    {0, 0, 0, 1}
  };
  Tuple b(1, 2, 3, 1);
  CHECK(A * b == Tuple(18, 24, 33, 1));
}

TEST_CASE("Multiplying a matrix by the identity matrix", "[matrices]")
{
  Matrix A = {
    {0, 1, 2, 4},
    {1, 2, 4, 8},
    {2, 4, 8, 16},
    {4, 8, 16, 32}
  };
  CHECK(A * Matrix::IdentityMatrix(4) == A);
}

TEST_CASE("Multiplying the identity matrix by a tuple", "[matrices]")
{
  Tuple a(1, 2, 3, 4);
  CHECK(Matrix::IdentityMatrix(4) * a == a);
}

TEST_CASE("Transposing a matrix", "[matrices]")
{
  Matrix A = {
    {0, 9, 3, 0},
    {9, 8, 0, 8},
    {1, 8, 5, 3},
    {0, 0, 5, 8}
  };
  Matrix expected = {
    {0, 9, 1, 0},
    {9, 8, 8, 0},
    {3, 0, 5, 5},
    {0, 8, 3, 8}
  };
  CHECK(A.Transpose() == expected);
}

TEST_CASE("Transposing the identity matrix", "[matrices]")
{
  auto A = Matrix::IdentityMatrix(4).Transpose();
  CHECK(A == Matrix::IdentityMatrix(4));
}

TEST_CASE("Calculating the determinant of a 2x2 matrix", "[matrices]")
{
  Matrix A = {
    {1, 5},
    {-3, 2}
  };
  CHECK(A.Determinant() == 17);
}

TEST_CASE("A submatrix of a 3x3 matrix is a 2x2 matrix", "[matrices]")
{
  Matrix A = {
    {1, 5, 0},
    {-3, 2, 7},
    {0, 6, -3}
  };
  Matrix expected = {
    {-3, 2},
    {0, 6}
  };
  CHECK(A.Submatrix(0, 2) == expected);
}

TEST_CASE("A submatrix of a 4x4 matrix is a 3x3 matrix", "[matrices]")
{
  Matrix A = {
    {-6, 1, 1, 6},
    {-8, 5, 8, 6},
    {-1, 0, 8, 2},
    {-7, 1, -1, 1}
  };
  Matrix expected = {
    {-6, 1, 6},
    {-8, 8, 6},
    {-7, -1, 1}
  };
  CHECK(A.Submatrix(2, 1) == expected);
}

TEST_CASE("Calculating a minor of a 3x3 matrix", "[matrices]")
{
  Matrix A = {
    {3, 5, 0},
    {2, -1, -7},
    {6, -1, 5}
  };
  Matrix B = A.Submatrix(1, 0);
  CHECK(B.Determinant() == 25);
  CHECK(A.Minor(1, 0) == 25);
}

TEST_CASE("Calculating a cofactor of a 3x3 matrix", "[matrices]")
{
  Matrix A = {
    {3, 5, 0},
    {2, -1, -7},
    {6, -1, 5}
  };
  CHECK(A.Minor(0, 0) == -12);
  CHECK(A.Cofactor(0, 0) == -12);
  CHECK(A.Minor(1, 0) == 25);
  CHECK(A.Cofactor(1, 0) == -25);
}

TEST_CASE("Calculating the determinant of a 3x3 matrix", "[matrices]")
{
  Matrix A = {
    {1, 2, 6},
    {-5, 8, -4},
    {2, 6, 4}
  };
  CHECK(A.Cofactor(0, 0) == 56);
  CHECK(A.Cofactor(0, 1) == 12);
  CHECK(A.Cofactor(0, 2) == -46);
  CHECK(A.Determinant() == -196);
}

TEST_CASE("Calculating the determinant of a 4x4 matrix", "[matrices]")
{
  Matrix A = {
    {-2, -8, 3, 5},
    {-3, 1, 7, 3},
    {1, 2, -9, 6},
    {-6, 7, 7, -9}
  };
  CHECK(A.Cofactor(0, 0) == 690);
  CHECK(A.Cofactor(0, 1) == 447);
  CHECK(A.Cofactor(0, 2) == 210);
  CHECK(A.Cofactor(0, 3) == 51);
  CHECK(A.Determinant() == -4071);
}

TEST_CASE("Testing an invertible matrix for invertibility", "[matrices]")
{
  Matrix A = {
    {6, 4, 4, 4},
    {5, 5, 7, 6},
    {4, -9, 3, -7},
    {9, 1, 7, -6}
  };
  CHECK(A.Determinant() == -2120);
  CHECK(A.IsInvertible());
}

TEST_CASE("Testing a non-invertible matrix for invertibility", "[matrices]")
{
  Matrix A = {
    {-4, 2, -2, -3},
    {9, 6, 2, 6},
    {0, -5, 1, -5},
    {0, 0, 0, 0}
  };
  CHECK(A.Determinant() == 0);
  CHECK_FALSE(A.IsInvertible());
}

TEST_CASE("Calculating the inverse of a matrix", "[matrices]")
{
  Matrix A = {
    {-5, 2, 6, -8},
    {1, -5, 1, 8},
    {7, 7, -6, -7},
    {1, -3, 7, 4}
  };
  Matrix B = A.Inverse();
  CHECK(A.Determinant() == 532);
  CHECK(A.Cofactor(2, 3) == -160);
  CHECK(B[3][2] == -160.0/532.0);
  CHECK(A.Cofactor(3, 2) == 105);
  CHECK(B[2][3] == 105.0/532.0);
  Matrix expected = {
    {0.21805, 0.45113, 0.24060, -0.04511},
    {-0.80827, -1.45677, -0.44361, 0.52068},
    {-0.07895, -0.22368, -0.05263, 0.19737},
    {-0.52256, -0.81391, -0.30075, 0.30639}
  };
  CHECK(B.ApproximatelyEqual(expected));
}

TEST_CASE("Calculating the inverse of another matrix", "[matrices]")
{
  Matrix A = {
    {8, -5, 9, 2},
    {7, 5, 6, 1},
    {-6, 0, 9, 6},
    {-3, 0, -9, -4}
  };
  Matrix expected = {
    {-0.15385, -0.15385, -0.28205, -0.53846},
    {-0.07692, 0.12308, 0.02564, 0.03077},
    {0.35897, 0.35897, 0.43590, 0.92308},
    {-0.69231, -0.69231, -0.76923, -1.92308}
  };
  CHECK(A.Inverse().ApproximatelyEqual(expected));
}

TEST_CASE("Calculating the inverse of a third matrix", "[matrices]")
{
  Matrix A = {
    {9, 3, 0, 9},
    {-5, -2, -6, -3},
    {-4, 9, 6, 4},
    {-7, 6, 6, 2}
  };
  Matrix expected = {
    {-0.04074, -0.07778, 0.14444, -0.22222},
    {-0.07778, 0.03333, 0.36667, -0.33333},
    {-0.02901, -0.14630, -0.10926, 0.12963},
    {0.17778, 0.06667, -0.26667, 0.33333}
  };
  CHECK(A.Inverse().ApproximatelyEqual(expected));
}

TEST_CASE("Multiplying a product by its inverse", "[matrices]")
{
  Matrix A = {
    {3, -9, 7, 3},
    {3, -8, 2, -9},
    {-4, 4, 4, 1},
    {-6, 5, -1, 1}
  };
  Matrix B = {
    {8, 2, 2, 2},
    {3, -1, 7, 0},
    {7, 0, 5, 4},
    {6, -2, 0, 5}
  };
  CHECK(A * B * B.Inverse() == A);
}
