#pragma once

#include <array>

#include "tuple.h"

class MatrixRow
{
public:
  /// \brief Construct a MatrixRow filled with zeros.
  MatrixRow();

  /// \brief Construct a MatrixRow with an initializer list.
  /// \param[in] list The initializer list.
  MatrixRow(const std::initializer_list<double>& list);

  /// \brief Array operator to access row elements.
  /// \param[in] colIndex The element index to access.
  /// \return The element value.
  double& operator[](size_t colIndex);

  /// \brief Array operator to access row elements from a const MatrixRow.
  /// \param[in] colIndex The element index to access.
  /// \return The element value.
  double operator[](size_t colIndex) const;

  /// \brief Equals operator to determine if two MatrixRows are equal.
  /// \param[in] a The row to compare against.
  /// \return True if all of the row values are approximately equal.
  bool operator==(const MatrixRow& a) const;

  /// \brief Not equal operator to determine if two MatrixRows are not equal.
  /// \param[in] a The row to compare against.
  /// \return True if the row values are not approximately equal.
  bool operator!=(const MatrixRow& a) const;

protected:
  std::array<double, 4> m_; ///< Values for the row.
};

class Matrix
{
public:
  /// \brief Construct a Matrix of given size filled with zeros.
  /// \param[in] size The number of rows and columns in the matrix.
  explicit Matrix(size_t size = 4);

  /// \brief Construct a Matrix with an initializer list.
  /// \param[in] list The initializer list.
  Matrix(const std::initializer_list<MatrixRow>& list);

  /// \brief Get the number of rows and columns of the matrix.
  /// \result The number of rows and column of the matrix.
  size_t Size() const { return size_; }

  /// \brief Array operator to access a MatrixRow.
  /// \param[in] rowIndex The row index to access.
  /// \return The matrix row.
  MatrixRow& operator[](size_t rowIndex);

  /// \brief Array operator to access a MatrixRow.
  /// \param[in] rowIndex The row index to access.
  /// \return The matrix row.
  const MatrixRow& operator[](size_t rowIndex) const;

  /// \brief Equals operator to determine if two matrices are equal.
  /// \param[in] a The matrix to compare against.
  /// \return True if the matrix values are approximately equal.
  bool operator==(const Matrix& a) const;

  /// \brief Not equal operator to determine if two matrices are not equal.
  /// \param[in] a The matrix to compare against.
  /// \return True if the matrix values are not approximately equal.
  bool operator!=(const Matrix& a) const;

  /// \brief Return an indentity matrix of given size.
  /// \param[in] size The size of the identity matrix.
  /// \return An identity matrix.
  static Matrix IdentityMatrix(size_t size);

  /// \brief Get the transpose of the matrix.
  /// \return The transpose of the matrix.
  Matrix Transpose() const;

  /// \brief Get the determinant of the matrix.
  /// \return The determinant of the matrix.
  double Determinant() const;

  /// \brief Return a submatrix with given row and column removed.
  /// \param[in] rowRemoved The row to be removed.
  /// \param[in] colRemoved The column to be removed.
  /// \return The submatrix of the matrix with given row and column removed.
  Matrix Submatrix(int rowRemoved, int colRemoved) const;

  /// \brief Return the minor with given row and column removed.
  /// \param[in] rowRemoved The row to be removed.
  /// \param[in] colRemoved The column to be removed.
  /// \return The minor of the matrix.
  double Minor(int rowRemoved, int colRemoved) const;

  /// \brief Return the cofactor with given row and column removed.
  /// \param[in] rowRemoved The row to be removed.
  /// \param[in] colRemoved The column to be removed.
  /// \return The cofactor of the matrix.
  double Cofactor(int rowRemoved, int colRemoved) const;

  /// \brief Determine if the matrix is invertible.
  /// \return True if the matrix is invertible.
  bool IsInvertible() const;

  /// \brief Return the inverse of the matrix.
  /// \return The inverse of the matrix.
  Matrix Inverse() const;

  /// \brief Determine if the matrix is approximately equal to given matrix.
  /// \param[in] a The matrix to compare against.
  /// \return True if all elements are equal within 4 significant digits.
  bool ApproximatelyEqual(const Matrix& a) const;

public:
  std::array<MatrixRow, 4> m_; ///< The rows of the matrix.
  size_t size_;                ///< The size of the matrix.
};

/// \brief Multiply two matrices.
/// \param[in] a The first matrix.
/// \param[in] b The second matrix.
/// \return The result of multiplying two matrices.
Matrix operator*(const Matrix& a, const Matrix& b);

/// \brief Multiply a matrix by a tuple.
/// \param[in] a The matrix.
/// \param[in] b The tuple.
/// \return The tuple resulting from the multiplication.
Tuple operator*(const Matrix& a, const Tuple& b);
