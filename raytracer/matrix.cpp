#include <raytracer/matrix.h>
#include <raytracer/test_utils.h>


MatrixRow::MatrixRow()
: m_{0}
{
}


MatrixRow::MatrixRow(const std::initializer_list<double>& list)
: m_{}
{
  auto it = m_.begin();
  size_t size = 0;
  for (auto& element : list)
  {
    if (size < 4)
    {
      *it = element;
      ++it;
    }
    ++size;
  }
}


double& MatrixRow::operator[](size_t i)
{
  return m_[i];
}


double MatrixRow::operator[](size_t i) const
{
  return m_[i];
}


bool MatrixRow::operator==(const MatrixRow& a) const
{
  bool equal = this->m_ == a.m_;
  return equal;
}


bool MatrixRow::operator!=(const MatrixRow& a) const
{
  bool equal = this->m_ != a.m_;
  return equal;
}


MatrixRow& Matrix::operator[](size_t colIndex)
{
  return m_[colIndex];
}


const MatrixRow& Matrix::operator[](size_t colIndex) const
{
  return m_[colIndex];
}


Matrix::Matrix(size_t size)
: m_{}
, size_(size)
{
  if (size > 4)
    size_ = 4;
}


Matrix::Matrix(const std::initializer_list<MatrixRow>& list)
: m_{}
, size_(0)
{
  auto it = m_.begin();
  for (auto& element : list)
  {
    if (size_ < 4)
    {
      *it = element;
      ++it;
      ++size_;
    }
  }
}


bool Matrix::operator==(const Matrix& a) const
{
  for (int row = 0; row < size_; ++row)
  {
    for (int col = 0; col < size_; ++col)
    {
      if (m_[row][col] != a[row][col])
        return false;
    }
  }
  return true;
}


bool Matrix::operator!=(const Matrix& a) const
{
  bool equal = *this == a;
  return !equal;
}


Tuple operator*(const Matrix& a, const Tuple& b)
{
  double t[4] = {b.x, b.y, b.z, b.w};
  double r[4];
  for (size_t row = 0; row < a.Size(); ++row)
  {
    double sum = 0.0;
    for (size_t col = 0; col < a.Size(); ++col)
    {
      sum += t[col] * a[row][col];
    }
    r[row] = sum;
  }
  return {r[0], r[1], r[2], r[3]};
}


Matrix Matrix::IdentityMatrix(size_t size)
{
  Matrix a(size);
  for (size_t i = 0; i < size; ++i)
    a[i][i] = 1;
  return a;
}


Matrix Matrix::Transpose() const
{
  Matrix a;
  for (size_t row = 0; row < size_; ++row)
  {
    for (size_t col = 0; col < size_; ++col)
    {
      a[col][row] = m_[row][col];
    }
  }
  return a;
}


double Matrix::Determinant() const
{
  double det = 0;

  if (size_ == 2)
  {
    det = m_[0][0] * m_[1][1] - m_[0][1] * m_[1][0];
  }
  else
  {
    for (int column = 0; column < size_; ++column)
    {
      det += m_[0][column] * Cofactor(0, column);
    }
  }
  return det;
}


Matrix Matrix::Submatrix(int rowRemoved, int colRemoved) const
{
  Matrix a(size_ - 1);
  for (size_t row = 0; row < size_ - 1; ++row)
  {
    for (size_t col = 0; col < size_ - 1; ++col)
    {
      size_t rowFrom = row;
      size_t colFrom = col;
      if (row >= rowRemoved)
        ++rowFrom;
      if (col >= colRemoved)
        ++colFrom;
      a[row][col] = m_[rowFrom][colFrom];
    }
  }
  return a;
}


double Matrix::Minor(int rowRemoved, int colRemoved) const
{
  double d = Submatrix(rowRemoved, colRemoved).Determinant();
  return d;
}


double Matrix::Cofactor(int rowRemoved, int colRemoved) const
{
  double d = Minor(rowRemoved, colRemoved);
  if ((static_cast<unsigned int>(rowRemoved + colRemoved) & 1) == 0)
    return d;
  else
    return -d;
}


bool Matrix::IsInvertible() const
{
  return Determinant() != 0.0;
}


Matrix Matrix::Inverse() const
{
  Matrix a;
  for (int row = 0; row < size_; ++row)
  {
    for (int col = 0; col < size_; ++col)
    {
      double c = Cofactor(row, col);
      // note that "col, row" here, instead of "row, col",
      // accomplishes the transpose operation!
      a[col][row] = c / Determinant();
    }
  }
  return a;
}


bool Matrix::ApproximatelyEqual(const Matrix& b) const
{
  for (int row = 0; row < size_; ++row)
  {
    for (int col = 0; col < size_; ++col)
    {
      if (!::ApproximatelyEqual(m_[row][col], b[row][col]))
        return false;
    }
  }
  return true;
}


bool Matrix::NearlyEqual(const Matrix& b) const
{
  for (int row = 0; row < size_; ++row)
  {
    for (int col = 0; col < size_; ++col)
    {
      if (!::NearlyEqual(m_[row][col], b[row][col]))
        return false;
    }
  }
  return true;
}


Matrix operator*(const Matrix& a, const Matrix& b)
{
  Matrix c;
  for (size_t row = 0; row < a.Size(); ++row)
  {
    for (size_t col = 0; col < a.Size(); ++col)
    {
      double sum = 0.0;
      for (size_t k = 0; k < a.Size(); ++k)
      {
        sum += a[row][k] * b[k][col];
      }
      c[row][col] = sum;
    }
  }
  return c;
}
