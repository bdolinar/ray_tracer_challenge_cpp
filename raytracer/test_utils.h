#pragma once

/// Determine if two doubles are approximately equal.
/// \param a The first double.
/// \param b The second double.
bool ApproximatelyEqual(double a, double b);
/// Determine if two doubles are nearly equal.
/// \param a The first double.
/// \param b The second double.
bool NearlyEqual(double a, double b);
/// Determine if two doubles are equal within a given number of digits.
/// \param a The first double.
/// \param b The second double.
bool EqualToDigits(double a, double b, int digits);
