
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
  Tuple eyePoint = point(0, 0, 10);
  Sphere sphere;
  Material material;
    material.set_color(Color(1, 0.2, 1));
  //material.ambient(0.2);
    sphere.set_material(material);
  
  Tuple lightPosition = point(-10, 10, 10);
  Color lightColor = Color(1, 1, 1);
  Light light(lightPosition, lightColor);

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
      Tuple rayVector = (point(x, y, 1.0) - eyePoint).normalize();
      Ray ray(eyePoint, rayVector);
      const Intersection* hit = hit(sphere.intersect(ray));
      if (hit)
      {
        Tuple point = ray.position(hit->t());
        Tuple normal = hit->object().normal_at(point);
        Tuple eyeVector = -ray.direction();
        Color color = lighting(hit->object().material(), light, point, eyeVector, normal);
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
