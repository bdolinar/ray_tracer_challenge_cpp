#pragma once

#include <raytracer/color.h>

#include <fstream>
#include <vector>


/// Canvas that pixels are stored in.
class Canvas
{
public:
  /// Construct a Canvas.
  /// \param a_width The number of pixels in horizontal direction.
  /// \param a_height The number of pixels in the vertical direction.
  Canvas(int a_width, int a_height);

  /// Get the horizontal width of the canvas.
  /// \return The horizontal width of the canvas.
  int width() const
  {
    return width_;
  }

  /// Get the height of the canvas.
  /// \return The height of the canvas.
  int height() const
  {
    return height_;
  }

  /// Write a pixel to the canvas.
  /// \param a_h The horizontal position of the pixel.
  /// \param a_v The vertical position of the pixel.
  /// \param a_color The color to be written.
  void write_pixel(int a_h, int a_v, const Color& a_color);

  /// Get the color of a pixel.
  /// \param a_h The horizontal position of the pixel.
  /// \param a_v The vertical position of the pixel.
  /// \return The color of the pixel.
  Color pixel_at(int a_h, int a_v) const;

  /// Determine if all of the pixels are a given color.
  /// \param a_color The color to compare all of the pixels too.
  /// \return True if all of the pixels are the given color.
  bool all_pixels_are_color(const Color& a_color) const;

  /// Set canvas pixels all to a given color.
  /// \param a_color The color to set all pixels too.
  void set_all_pixel_colors(const Color& a_color);

  /// Export canvas to PPM file.
  /// \param a_output The output stream to write the file too.
  void to_ppm_file(std::ostream& a_output) const;

  /// Export canvas to PPM file.
  /// \return The PPM file contents as a string.
  std::string to_ppm_string() const;

private:
  int width_ = 0;        ///< The number of pixels in horizontal direction.
  int height_ = 0;       ///< The number of pixels in the vertical direction.
  std::vector<std::vector<Color>> pixels_; ///< The storage for the pixels.
};
