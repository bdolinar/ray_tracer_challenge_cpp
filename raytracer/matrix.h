#pragma once

#include <array>

#include <raytracer/tuple.h>

#undef minor
#undef major


/// A row in a matrix.
class MatrixRow
{
public:
  /// Construct a MatrixRow filled with zeros.
  MatrixRow();

  /// Construct a MatrixRow with an initializer list.
  /// \param a_list The initializer list.
  MatrixRow(const std::initializer_list<double>& a_list);

  /// Array operator to access row elements.
  /// \param a_col_index The element index to access.
  /// \return The element value.
  double& operator[](size_t a_col_index);

  /// Array operator to access row elements from a const MatrixRow.
  /// \param a_col_index The element index to access.
  /// \return The element value.
  double operator[](size_t a_col_index) const;

  /// Equals operator to determine if two MatrixRows are equal.
  /// \param a_rhs The row to compare against.
  /// \return True if all of the row values are approximately equal.
  bool operator==(const MatrixRow& a_rhs) const;

  /// Not equal operator to determine if two MatrixRows are not equal.
  /// \param a_rhs The row to compare against.
  /// \return True if the row values are not approximately equal.
  bool operator!=(const MatrixRow& a_rhs) const;

protected:
  std::array<double, 4> m_; ///< Values for the row.
};

/// A matrix that can be from size 1x1 to 4x4.
class Matrix
{
public:
  /// Construct a Matrix of given size filled with zeros.
  /// \param a_size The number of rows and columns in the matrix.
  explicit Matrix(size_t a_size = 4);

  /// Construct a Matrix with an initializer list.
  /// \param a_list The initializer list.
  Matrix(const std::initializer_list<MatrixRow>& a_list);

  /// Get the number of rows and columns of the matrix.
  /// \result The number of rows and column of the matrix.
  size_t size() const
  {
    return size_;
  }

  /// Array operator to access a MatrixRow.
  /// \param a_row_index The row index to access.
  /// \return The matrix row.
  MatrixRow& operator[](size_t a_row_index);

  /// Array operator to access a MatrixRow.
  /// \param a_row_index The row index to access.
  /// \return The matrix row.
  const MatrixRow& operator[](size_t a_row_index) const;

  /// Equals operator to determine if two matrices are equal.
  /// \param a_rhs The matrix to compare against.
  /// \return True if the matrix values are approximately equal.
  bool operator==(const Matrix& a_rhs) const;

  /// Not equal operator to determine if two matrices are not equal.
  /// \param a_rhs The matrix to compare against.
  /// \return True if the matrix values are not approximately equal.
  bool operator!=(const Matrix& a_rhs) const;

  /// Return an identity matrix of given size.
  /// \param a_size The size of the identity matrix.
  /// \return An identity matrix.
  static Matrix identity_matrix(size_t a_size = 4);

  /// Get the transpose of the matrix.
  /// \return The transpose of the matrix.
  Matrix transpose() const;

  /// Get the determinant of the matrix.
  /// \return The determinant of the matrix.
  double determinant() const;

  /// Return a sub matrix with given row and column removed.
  /// \param a_row_removed The row to be removed.
  /// \param a_col_removed The column to be removed.
  /// \return The submatrix of the matrix with given row and column removed.
  Matrix sub_matrix(int a_row_removed, int a_col_removed) const;

  /// Return the minor with given row and column removed.
  /// \param a_row_removed The row to be removed.
  /// \param a_col_removed The column to be removed.
  /// \return The minor of the matrix.
  double minor(int a_row_removed, int a_col_removed) const;

  /// Return the cofactor with given row and column removed.
  /// \param a_row_removed The row to be removed.
  /// \param a_col_removed The column to be removed.
  /// \return The cofactor of the matrix.
  double cofactor(int a_row_removed, int a_col_removed) const;

  /// Determine if the matrix is invertible.
  /// \return True if the matrix is invertible.
  bool is_invertible() const;

  /// Return the inverse of the matrix.
  /// \return The inverse of the matrix.
  Matrix inverse() const;

  /// Determine if the matrix is approximately equal to given matrix.
  /// \param a_rhs The matrix to compare against.
  /// \return True if all elements are equal within 4 significant digits.
  bool approximately_equal(const Matrix& a_rhs) const;

  /// Determine if the matrix is nearly equal to given matrix.
  /// \param a_rhs The matrix to compare against.
  /// \return True if all elements are equal within 10 significant digits.
  bool nearly_equal(const Matrix& a_rhs) const;

public:
  std::array<MatrixRow, 4> m_; ///< The rows of the matrix.
  size_t size_;                ///< The size of the matrix.
};

/// Multiply two matrices.
/// \param a_lhs The first matrix.
/// \param a_rhs The second matrix.
/// \return The result of multiplying two matrices.
Matrix operator*(const Matrix& a_lhs, const Matrix& a_rhs);

/// Multiply a matrix by a tuple.
/// \param a_lhs The matrix.
/// \param a_rhs The tuple.
/// \return The tuple resulting from the multiplication.
Tuple operator*(const Matrix& a_lhs, const Tuple& a_rhs);
