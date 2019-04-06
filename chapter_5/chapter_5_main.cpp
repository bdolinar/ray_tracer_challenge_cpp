
#include <fstream>

#include <raytracer/canvas.h>
#include <raytracer/intersection.h>
#include <raytracer/light.h>
#include <raytracer/material.h>
#include <raytracer/ray.h>
#include <raytracer/sphere.h>
#include <raytracer/transform.h>

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
      Tuple rayVector = (Point(x, y, 1.0) - eye).Normalize();
      Ray ray(eye, rayVector);
      const Intersection* hit = Hit(sphere.Intersect(ray));
      if (hit)
      {
        Color color = red;
        canvas.WritePixel(h, v, color);
      }
      else
      {
        canvas.WritePixel(h, v, black);
      }
    }
  }
  
  std::ofstream outfile;
  outfile.open ("output.ppm");
  canvas.ToPpmFile(outfile);
  return 0;
}
