#include <catch2/catch.hpp>

#include <raytracer/canvas.h>
#include <raytracer/tuple.h>

namespace {

std::string ExtractLines(const std::string& lines, int first_line, int last_line)
{
  std::string extracted;
  size_t length = lines.size();
  size_t start = 0;
  int line_number = 1;
  while (start < length && line_number <= last_line)
  {
    size_t line_end = lines.find("\r\n", start);
    if (line_end == std::string::npos)
      line_end = lines.find("\n", start);
    if (line_end == std::string::npos)
      line_end = length;
    if (line_number >= first_line && line_number <= last_line)
    {
      extracted += lines.substr(start, line_end - start) + '\n';
    }
    start = line_end + 1;
    ++line_number;
  }
  return extracted;
}

bool EndsInNewLine(const std::string& s)
{
  return !s.empty() && s.back() == '\n';
}

} // namespace {

TEST_CASE("Creating a canvas", "[canvas]")
{
  Canvas c(10, 20);
  CHECK(c.Width() == 10);
  CHECK(c.Height() == 20);
  CHECK(c.AllPixelsAreColor(Color(0, 0, 0)));
}

TEST_CASE("Writing pixels to a canvas", "[canvas]")
{
  Canvas c(10, 20);
  Color red(1, 0, 0);
  c.WritePixel(2, 3, red);
  CHECK(c.PixelAt(2, 3) == red);
}

TEST_CASE("Constructing the PPM header", "[canvas]")
{
  Canvas c(5, 3);
  std::string ppm = c.ToPpmText();
  std::string ppm_lines = ExtractLines(ppm, 1, 3);
  std::string expected_ppm_lines = 
    "P3\n"
    "5 3\n"
    "255\n";
  CHECK(expected_ppm_lines == ppm_lines);
}

TEST_CASE("Constructing the PPM pixel data", "[canvas]")
{
  Canvas c(5, 3);
  Color c1(1.5, 0, 0);
  Color c2(0, 0.5, 0);
  Color c3(-0.5, 0, 1);
  c.WritePixel(0, 0, c1);
  c.WritePixel(2, 1, c2);
  c.WritePixel(4, 2, c3);
  std::string ppm = c.ToPpmText();
  std::string ppm_lines = ExtractLines(ppm, 4, 6);
  std::string expected_ppm_lines = 
    "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
    "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
    "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n";
  CHECK(expected_ppm_lines == ppm_lines);
}

TEST_CASE("Splitting long lines in PPM files", "[canvas]")
{
  Canvas c(10, 2);
  c.SetAllPixelColors(Color(1, 0.8, 0.6));
  std::string ppm = c.ToPpmText();
  std::string ppm_lines = ExtractLines(ppm, 4, 7);
  std::string expected_ppm_lines = 
    "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
    "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
    "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
    "153 255 204 153 255 204 153 255 204 153 255 204 153\n";
  CHECK(expected_ppm_lines == ppm_lines);
}

TEST_CASE("PPM files are terminated by a newline", "[canvas]")
{
  Canvas c(5, 3);
  std::string ppm = c.ToPpmText();
  CHECK(EndsInNewLine(ppm));
}
