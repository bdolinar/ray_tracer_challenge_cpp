#include <raytracer/canvas.h>

#include <sstream>


namespace
{
//------------------------------------------------------------------------------
int scale_fraction(double a_val, int a_upper_value)
{
  int result = static_cast<int>(a_val * (a_upper_value + 1));
  if (result > a_upper_value)
    result = a_upper_value;
  else if (result < 0)
    result = 0;
  return result;
}

//------------------------------------------------------------------------------
void write_ppm_value(std::ostream& a_out, int a_value, int& a_line_length)
{
  std::string out_value = std::to_string(a_value);
  int value_length = (int) out_value.size();
  if (a_line_length + value_length + 1 > 70)
  {
    a_out << '\n';
    a_line_length = 0;
  }
  if (a_line_length != 0)
  {
    a_out << " ";
    ++a_line_length;
  }
  a_out << a_value;
  a_line_length += value_length;
}
} // namespace

//------------------------------------------------------------------------------
Canvas::Canvas(int a_width, int a_height)
    : width_(a_width)
      , height_(a_height)
{
  pixels_.resize(a_height, std::vector<Color>(a_width));
}

//------------------------------------------------------------------------------
void Canvas::write_pixel(int a_h, int a_v, const Color& a_color)
{
  pixels_[a_v][a_h] = a_color;
}

//------------------------------------------------------------------------------
Color Canvas::pixel_at(int a_h, int a_v) const
{
  return pixels_[a_v][a_h];
}

//------------------------------------------------------------------------------
bool Canvas::all_pixels_are_color(const Color& a_color) const
{
  for (auto& row : pixels_)
  {
    for (auto& pixel : row)
    {
      if (!(pixel == a_color))
      {
        return false;
      }
    }
  }
  return true;
}

//------------------------------------------------------------------------------
void Canvas::set_all_pixel_colors(const Color& a_color)
{
  for (auto& row : pixels_)
  {
    for (auto& pixel : row)
    {
      pixel = a_color;
    }
  }
}

//------------------------------------------------------------------------------
void Canvas::to_ppm_file(std::ostream& a_output) const
{
  a_output << "P3\n";
  a_output << width_ << " " << height_ << "\n";
  a_output << "255\n";

  for (auto& row : pixels_)
  {
    int line_length = 0;
    for (auto& pixel : row)
    {
      int red = scale_fraction(pixel.red(), 255);
      write_ppm_value(a_output, red, line_length);
      int green = scale_fraction(pixel.green(), 255);
      write_ppm_value(a_output, green, line_length);
      int blue = scale_fraction(pixel.blue(), 255);
      write_ppm_value(a_output, blue, line_length);
    }
    a_output << '\n';
  }
}

//------------------------------------------------------------------------------
std::string Canvas::to_ppm_string() const
{
  std::ostringstream out;
  to_ppm_file(out);
  return out.str();
}
