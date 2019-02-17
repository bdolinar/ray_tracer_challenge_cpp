#include <raytracer/canvas.h>

#include <sstream>

namespace
{
int scale_fraction(double val, int scale_to)
{
  int result = val * (scale_to + 1);
  if (result > scale_to)
    result = scale_to;
  else if (result < 0)
    result = 0;
  return result;
}

void write_ppm_value(std::ostream& out, int value, int& line_length)
{
  std::string out_value = std::to_string(value);
  int value_length = (int)out_value.size();
  if (line_length + value_length + 1 > 70)
  {
    out << '\n';
    line_length = 0;
  }
  if (line_length != 0)
  {
    out << " ";
    ++line_length;
  }
  out << value;
  line_length += value_length;
}

} // namespace

Canvas::Canvas(int width, int height)
: width_(width)
, height_(height)
{
  pixels_.resize(height, std::vector<Color>(width));
}

void Canvas::WritePixel(int h, int v, const Color& color)
{
  pixels_[v][h] = color;
}

Color Canvas::PixelAt(int h, int v) const
{
  return pixels_[v][h];
}

bool Canvas::AllPixelsAreColor(const Color& color) const
{
  for (auto& row : pixels_)
  {
    for (auto& pixel : row)
    {
      if (!(pixel == color))
      {
        return false;
      }
    }
  }
  return true;
}

void Canvas::SetAllPixelColors(const Color& color)
{
  for (auto& row : pixels_)
  {
    for (auto& pixel : row)
    {
      pixel = color;
    }
  }
}

std::string Canvas::ToPpmText() const
{
  std::ostringstream out;
  out << "P3\n";
  out << width_ << " " << height_ << "\n";
  out << "255\n";

  for (auto& row : pixels_)
  {
    int line_length = 0;
    for (auto& pixel : row)
    {
      int red = scale_fraction(pixel.Red(), 255);
      write_ppm_value(out, red, line_length);
      int green = scale_fraction(pixel.Green(), 255);
      write_ppm_value(out, green, line_length);
      int blue = scale_fraction(pixel.Blue(), 255);
      write_ppm_value(out, blue, line_length);
    }
    out << '\n';
  }
  return out.str();
}
