#pragma once

/// Determine if two doubles are approximately equal.
/// \param a_lhs The first double.
/// \param a_rhs The second double.
bool approximately_equal(double a_lhs, double a_rhs);

/// Determine if two doubles are nearly equal.
/// \param a_lhs The first double.
/// \param a_rhs The second double.
bool nearly_equal(double a_lhs, double a_rhs);

/// Determine if two doubles are equal within a given number of digits.
/// \param a_lhs The first double.
/// \param a_rhs The second double.
bool equal_to_digits(double a_lhs, double a_rhs, int a_digits);
