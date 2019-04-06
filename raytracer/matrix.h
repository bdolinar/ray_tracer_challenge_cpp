#pragma once

#include <array>

#include <raytracer/tuple.h>

/// A row in a matrix.
class MatrixRow
{
public:
  /// Construct a MatrixRow filled with zeros.
  MatrixRow();

  /// Construct a MatrixRow with an initializer list.
  /// \param list The initializer list.
  MatrixRow(const std::initializer_list<double>& list);

  /// Array operator to access row elements.
  /// \param colIndex The element index to access.
  /// \return The element value.
  double& operator[](size_t colIndex);

  /// Array operator to access row elements from a const MatrixRow.
  /// \param colIndex The element index to access.
  /// \return The element value.
  double operator[](size_t colIndex) const;

  /// Equals operator to determine if two MatrixRows are equal.
  /// \param a The row to compare against.
  /// \return True if all of the row values are approximately equal.
  bool operator==(const MatrixRow& a) const;

  /// Not equal operator to determine if two MatrixRows are not equal.
  /// \param a The row to compare against.
  /// \return True if the row values are not approximately equal.
  bool operator!=(const MatrixRow& a) const;

protected:
  std::array<double, 4> m_; ///< Values for the row.
};

/// A matrix that can be from size 1x1 to 4x4.
class Matrix
{
public:
  /// Construct a Matrix of given size filled with zeros.
  /// \param size The number of rows and columns in the matrix.
  explicit Matrix(size_t size = 4);

  /// Construct a Matrix with an initializer list.
  /// \param list The initializer list.
  Matrix(const std::initializer_list<MatrixRow>& list);

  /// Get the number of rows and columns of the matrix.
  /// \result The number of rows and column of the matrix.
  size_t Size() const { return size_; }

  /// Array operator to access a MatrixRow.
  /// \param rowIndex The row index to access.
  /// \return The matrix row.
  MatrixRow& operator[](size_t rowIndex);

  /// Array operator to access a MatrixRow.
  /// \param rowIndex The row index to access.
  /// \return The matrix row.
  const MatrixRow& operator[](size_t rowIndex) const;

  /// Equals operator to determine if two matrices are equal.
  /// \param a The matrix to compare against.
  /// \return True if the matrix values are approximately equal.
  bool operator==(const Matrix& a) const;

  /// Not equal operator to determine if two matrices are not equal.
  /// \param a The matrix to compare against.
  /// \return True if the matrix values are not approximately equal.
  bool operator!=(const Matrix& a) const;

  /// Return an indentity matrix of given size.
  /// \param size The size of the identity matrix.
  /// \return An identity matrix.
  static Matrix IdentityMatrix(size_t size = 4);

  /// Get the transpose of the matrix.
  /// \return The transpose of the matrix.
  Matrix Transpose() const;

  /// Get the determinant of the matrix.
  /// \return The determinant of the matrix.
  double Determinant() const;

  /// Return a submatrix with given row and column removed.
  /// \param rowRemoved The row to be removed.
  /// \param colRemoved The column to be removed.
  /// \return The submatrix of the matrix with given row and column removed.
  Matrix Submatrix(int rowRemoved, int colRemoved) const;

  /// Return the minor with given row and column removed.
  /// \param rowRemoved The row to be removed.
  /// \param colRemoved The column to be removed.
  /// \return The minor of the matrix.
  double Minor(int rowRemoved, int colRemoved) const;

  /// Return the cofactor with given row and column removed.
  /// \param rowRemoved The row to be removed.
  /// \param colRemoved The column to be removed.
  /// \return The cofactor of the matrix.
  double Cofactor(int rowRemoved, int colRemoved) const;

  /// Determine if the matrix is invertible.
  /// \return True if the matrix is invertible.
  bool IsInvertible() const;

  /// Return the inverse of the matrix.
  /// \return The inverse of the matrix.
  Matrix Inverse() const;

  /// Determine if the matrix is approximately equal to given matrix.
  /// \param a The matrix to compare against.
  /// \return True if all elements are equal within 4 significant digits.
  bool ApproximatelyEqual(const Matrix& a) const;

  /// Determine if the matrix is nearly equal to given matrix.
  /// \param a The matrix to compare against.
  /// \return True if all elements are equal within 10 significant digits.
  bool NearlyEqual(const Matrix& a) const;

public:
  std::array<MatrixRow, 4> m_; ///< The rows of the matrix.
  size_t size_;                ///< The size of the matrix.
};

/// Multiply two matrices.
/// \param a The first matrix.
/// \param b The second matrix.
/// \return The result of multiplying two matrices.
Matrix operator*(const Matrix& a, const Matrix& b);

/// Multiply a matrix by a tuple.
/// \param a The matrix.
/// \param b The tuple.
/// \return The tuple resulting from the multiplication.
Tuple operator*(const Matrix& a, const Tuple& b);
