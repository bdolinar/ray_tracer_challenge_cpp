#include <raytracer/canvas.h>

#include <sstream>

namespace
{
int ScaleFraction(double val, int upperValue)
{
  int result = static_cast<int>(val * (upperValue + 1));
  if (result > upperValue)
    result = upperValue;
  else if (result < 0)
    result = 0;
  return result;
}


void WritePpmValue(std::ostream& out, int value, int& lineLength)
{
  std::string outValue = std::to_string(value);
  int valueLength = (int)outValue.size();
  if (lineLength + valueLength + 1 > 70)
  {
    out << '\n';
    lineLength = 0;
  }
  if (lineLength != 0)
  {
    out << " ";
    ++lineLength;
  }
  out << value;
  lineLength += valueLength;
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


void Canvas::ToPpmFile(std::ostream& output) const
{
  output << "P3\n";
  output << width_ << " " << height_ << "\n";
  output << "255\n";

  for (auto& row : pixels_)
  {
    int lineLength = 0;
    for (auto& pixel : row)
    {
      int red = ScaleFraction(pixel.Red(), 255);
      WritePpmValue(output, red, lineLength);
      int green = ScaleFraction(pixel.Green(), 255);
      WritePpmValue(output, green, lineLength);
      int blue = ScaleFraction(pixel.Blue(), 255);
      WritePpmValue(output, blue, lineLength);
    }
    output << '\n';
  }
}


std::string Canvas::ToPpmString() const
{
  std::ostringstream out;
  ToPpmFile(out);
  return out.str();
}
