#pragma once

#include "color.h"

#include <fstream>
#include <vector>

/// Canvas that pixels are stored in.
class Canvas
{
public:
  /// \brief Construct a Canvas.
  /// \param[in] aWidth The number of pixels in horizontal direction.
  /// \param[in] aHeight The number of pixels in the vertical direction.
  Canvas(int aWidth, int aHeight);

  /// \brief Get the horizontal width of the canvas.
  /// \return The horizontal width of the canvas.
  int Width() const { return width_; }

  /// \brief Get the height of the canvas.
  /// \return The height of the canvas.
  int Height() const { return height_; }

  /// \brief Write a pixel to the canvas.
  /// \param[in] h The horizontal position of the pixel.
  /// \param[in] v The vertical position of the pixel.
  /// \param[in] color The color to be written.
  void WritePixel(int h, int v, const Color& color);

  /// \brief Get the color of a pixel.
  /// \param[in] h The horizontal position of the pixel.
  /// \param[in] v The vertical position of the pixel.
  /// \return The color of the pixel.
  Color PixelAt(int h, int v) const;

  /// \brief Determine if all of the pixels are a given color.
  /// \param[in] color The color to compare all of the pixels too.
  /// \return True if all of the pixels are the given color.
  bool AllPixelsAreColor(const Color& color) const;

  /// \brief Set canvas pixels all to a given color.
  /// \param[in] color The color to set all pixels too.
  void SetAllPixelColors(const Color& color);

  /// \brief Export canvas to PPM file.
  /// \param[in] output The output stream to write the file too.
  void ToPpmFile(std::ostream& output) const;

  /// \brief Export canvas to PPM file.
  /// \return The PPM file contents as a string.
  std::string ToPpmString() const;

private:
  int width_ = 0;                          ///< The number of pixels in horizontal direction.
  int height_ = 0;                         ///< The number of pixels in the vertical direction.
  std::vector<std::vector<Color>> pixels_; ///< The storage for the pixels.
};
