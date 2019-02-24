
#define CATCH_CONFIG_RUNNER
#include <catch2/catch.hpp>

//#define CHAPTER_5
//#define CHAPTER_6
#if defined(CHAPTER_5) || defined(CHAPTER_6)

#include <fstream>

#include "canvas.h"
#include "intersection.h"
#include "light.h"
#include "material.h"
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
#ifdef CHAPTER_6
  Material material;
  material.Color(Color(1, 0.2, 1));
  //material.Ambient(0.2);
  sphere.Material(material);
  
  Tuple lightPosition = Point(-10, 10, 10);
  Color lightColor = Color(1, 1, 1);
  Light light(lightPosition, lightColor);
#endif
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
#ifdef CHAPTER_6
        Tuple point = ray.Position(hit->T());
        Tuple normal = hit->Object().NormalAt(point);
        Tuple eye = -ray.Direction();
        Color color = Lighting(hit->Object().Material(), light, point, eye, normal);
#else
        Color color = red;
#endif
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

#else

int main(int argc, char* argv[])
{
  int result = Catch::Session().run(argc, argv);
  return result;
}

#endif
