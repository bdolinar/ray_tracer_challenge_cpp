#include <raytracer/matrix.h>
#include <raytracer/test_utils.h>


//------------------------------------------------------------------------------
MatrixRow::MatrixRow()
    : m_{0}
{
}

//------------------------------------------------------------------------------
MatrixRow::MatrixRow(const std::initializer_list<double>& a_list)
    : m_{}
{
  auto it = m_.begin();
  size_t size = 0;
  for (auto& element : a_list)
  {
    if (size < 4)
    {
      *it = element;
      ++it;
    }
    ++size;
  }
}

//------------------------------------------------------------------------------
double& MatrixRow::operator[](size_t a_col_index)
{
  return m_[a_col_index];
}

//------------------------------------------------------------------------------
double MatrixRow::operator[](size_t a_col_index) const
{
  return m_[a_col_index];
}

//------------------------------------------------------------------------------
bool MatrixRow::operator==(const MatrixRow& a_rhs) const
{
  bool equal = this->m_ == a_rhs.m_;
  return equal;
}

//------------------------------------------------------------------------------
bool MatrixRow::operator!=(const MatrixRow& a_rhs) const
{
  bool equal = this->m_ != a_rhs.m_;
  return equal;
}

//------------------------------------------------------------------------------
MatrixRow& Matrix::operator[](size_t a_row_index)
{
  return m_[a_row_index];
}

//------------------------------------------------------------------------------
const MatrixRow& Matrix::operator[](size_t a_row_index) const
{
  return m_[a_row_index];
}

//------------------------------------------------------------------------------
Matrix::Matrix(size_t a_size)
    : m_{}
      , size_(a_size)
{
  if (a_size > 4)
    size_ = 4;
}

//------------------------------------------------------------------------------
Matrix::Matrix(const std::initializer_list<MatrixRow>& a_list)
    : m_{}
      , size_(0)
{
  auto it = m_.begin();
  for (auto& element : a_list)
  {
    if (size_ < 4)
    {
      *it = element;
      ++it;
      ++size_;
    }
  }
}

//------------------------------------------------------------------------------
bool Matrix::operator==(const Matrix& a_rhs) const
{
  for (int row = 0; row < size_; ++row)
  {
    for (int col = 0; col < size_; ++col)
    {
      if (m_[row][col] != a_rhs[row][col])
        return false;
    }
  }
  return true;
}

//------------------------------------------------------------------------------
bool Matrix::operator!=(const Matrix& a_rhs) const
{
  bool equal = *this == a_rhs;
  return !equal;
}

//------------------------------------------------------------------------------
Tuple operator*(const Matrix& a_lhs, const Tuple& a_rhs)
{
  double t[4] = {a_rhs.x(), a_rhs.y(), a_rhs.z(), a_rhs.w()};
  double r[4];
  for (size_t row = 0; row < a_lhs.size(); ++row)
  {
    double sum = 0.0;
    for (size_t col = 0; col < a_lhs.size(); ++col)
    {
      sum += t[col] * a_lhs[row][col];
    }
    r[row] = sum;
  }
  return {r[0], r[1], r[2], r[3]};
}

//------------------------------------------------------------------------------
Matrix Matrix::identity_matrix(size_t a_size)
{
  Matrix a(a_size);
  for (size_t i = 0; i < a_size; ++i)
  {
    a[i][i] = 1;
  }
  return a;
}

//------------------------------------------------------------------------------
Matrix Matrix::transpose() const
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

//------------------------------------------------------------------------------
double Matrix::determinant() const
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
      det += m_[0][column] * cofactor(0, column);
    }
  }
  return det;
}

//------------------------------------------------------------------------------
Matrix Matrix::sub_matrix(int a_row_removed, int a_col_removed) const
{
  Matrix a(size_ - 1);
  for (size_t row = 0; row < size_ - 1; ++row)
  {
    for (size_t col = 0; col < size_ - 1; ++col)
    {
      size_t row_from = row;
      size_t col_from = col;
      if (row >= a_row_removed)
        ++row_from;
      if (col >= a_col_removed)
        ++col_from;
      a[row][col] = m_[row_from][col_from];
    }
  }
  return a;
}

//------------------------------------------------------------------------------
double Matrix::minor(int a_row_removed, int a_col_removed) const
{
  double d = sub_matrix(a_row_removed, a_col_removed).determinant();
  return d;
}

//------------------------------------------------------------------------------
double Matrix::cofactor(int a_row_removed, int a_col_removed) const
{
  double d = minor(a_row_removed, a_col_removed);
  if ((static_cast<unsigned int>(a_row_removed + a_col_removed) & 1) == 0)
    return d;
  else
    return -d;
}

//------------------------------------------------------------------------------
bool Matrix::is_invertible() const
{
  return determinant() != 0.0;
}

//------------------------------------------------------------------------------
Matrix Matrix::inverse() const
{
  Matrix a;
  for (int row = 0; row < size_; ++row)
  {
    for (int col = 0; col < size_; ++col)
    {
      double c = cofactor(row, col);
      // note that "col, row" here, instead of "row, col",
      // accomplishes the transpose operation!
      a[col][row] = c / determinant();
    }
  }
  return a;
}

//------------------------------------------------------------------------------
bool Matrix::approximately_equal(const Matrix& a_rhs) const
{
  for (int row = 0; row < size_; ++row)
  {
    for (int col = 0; col < size_; ++col)
    {
      if (!::approximately_equal(m_[row][col], a_rhs[row][col]))
        return false;
    }
  }
  return true;
}

//------------------------------------------------------------------------------
bool Matrix::nearly_equal(const Matrix& a_rhs) const
{
  for (int row = 0; row < size_; ++row)
  {
    for (int col = 0; col < size_; ++col)
    {
      if (!::nearly_equal(m_[row][col], a_rhs[row][col]))
        return false;
    }
  }
  return true;
}

//------------------------------------------------------------------------------
Matrix operator*(const Matrix& a_lhs, const Matrix& a_rhs)
{
  Matrix c;
  for (size_t row = 0; row < a_lhs.size(); ++row)
  {
    for (size_t col = 0; col < a_lhs.size(); ++col)
    {
      double sum = 0.0;
      for (size_t k = 0; k < a_lhs.size(); ++k)
      {
        sum += a_lhs[row][k] * a_rhs[k][col];
      }
      c[row][col] = sum;
    }
  }
  return c;
}
