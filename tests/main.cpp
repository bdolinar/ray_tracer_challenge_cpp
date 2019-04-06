#if defined(CHAPTER_5)

#include <fstream>

#include "canvas.h"
#include "intersection.h"
#include "ray.h"
#include "sphere.h"
#include "transform.h"

int main(int argc, char* argv[])
{
  int HSIZE = 400;
  double HALF_HSIZE = HSIZE / 2.0;
  int VSIZE = 400;
  double HALF_VSIZE = VSIZE / 2.0;
  Tuple eye = Point(0, 0, 10);
  Sphere sphere;
//  sphere.Transform(Shearing(1, 0, 0, 0, 0, 0) * Scaling(0.5, 1.0, 1.0));
  Canvas canvas(HSIZE + 1, VSIZE + 1);
  Color red(1.0, 0, 0);
  Color black(0.0, 0.0, 0.0);
  for (int h = 0; h <= HSIZE; ++h)
  {
    double x = h / HALF_HSIZE - 1;
    for (int v = 0; v <= VSIZE; ++v)
    {
      double y = 1 - v / HALF_VSIZE;
      Ray ray(eye, Point(x, y, 1.0) - eye);
      Intersections intersections = sphere.Intersect(ray);
      if (intersections.empty())
        canvas.WritePixel(h, v, black);
      else
        canvas.WritePixel(h, v, red);
      //std::cout << "(" << x << ", " << y << ")\n";
    }
  }
  
  std::ofstream outfile;
  outfile.open ("output.ppm");
  canvas.ToPpmFile(outfile);
  return 0;
}

#else

#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

int main(int argc, char* argv[])
{
  int result = Catch::Session().run(argc, argv);
  return result;
}

#endif
