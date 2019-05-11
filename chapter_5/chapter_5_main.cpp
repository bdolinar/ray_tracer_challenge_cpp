
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
  Tuple eye = point(0, 0, 10);
  Sphere sphere;

  //  sphere.set_transform(shearing(1, 0, 0, 0, 0, 0) * scaling(0.5, 1.0, 1.0));
  Canvas canvas(HSIZE + 1, VSIZE + 1);
  Color red(1.0, 0, 0);
  Color black(0.0, 0.0, 0.0);
  for (int h = 0; h <= HSIZE; ++h)
  {
    double x = h / HALF_HSIZE - 1;
    for (int v = 0; v <= VSIZE; ++v)
    {
      double y = 1 - v / HALF_VSIZE;
      Tuple direction = (point(x, y, 1.0) - eye).normalize();
      Ray ray(eye, direction);
      auto i = sphere.intersect(ray);
      if (!i.empty())
      {
        Color color = red;
        canvas.write_pixel(h, v, color);
      }
      else
      {
        canvas.write_pixel(h, v, black);
      }
    }
  }
  
  std::ofstream outfile;
  outfile.open ("output.ppm");
  canvas.to_ppm_file(outfile);
  return 0;
}
