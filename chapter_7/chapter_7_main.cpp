
#include <fstream>

#include <raytracer/camera.h>
#include <raytracer/canvas.h>
#include <raytracer/intersection.h>
#include <raytracer/light.h>
#include <raytracer/material.h>
#include <raytracer/ray.h>
#include <raytracer/sphere.h>
#include <raytracer/transform.h>

int main(int argc, char* argv[])
{
  World world;

  Material floorMaterial;
    floorMaterial.set_color(Color(1, 0.9, 0.9));
    floorMaterial.set_specular(0);

  auto floor = Sphere::New();
  floor->Transform(scaling(10, 0.01, 10));
  floor->Material(floorMaterial);

  auto leftWall = Sphere::New();
  auto leftWallTransform = translation(0, 0, 5) * rotation_y(-M_PI_4) * rotation_x(M_PI_2) * scaling(10, 0.01, 10);
  leftWall->Transform(leftWallTransform);
  leftWall->Material(floorMaterial);

  auto rightWall = Sphere::New();
  auto rightWallTransform = translation(0, 0, 5) * rotation_y(M_PI_4) * rotation_x(M_PI_2) * scaling(10, 0.01, 10);
  rightWall->Transform(rightWallTransform);
  rightWall->Material(floorMaterial);

  auto middle = Sphere::New();
  middle->Transform(translation(-0.5, 1, 0.5));
  Material middleMaterial;
    middleMaterial.set_color(Color(0.1, 1, 0.5));
    middleMaterial.set_diffuse(0.7);
    middleMaterial.set_specular(0.3);
  middle->Material(middleMaterial);

  auto right = Sphere::New();
  right->Transform(translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5));
  Material rightMaterial;
    rightMaterial.set_color(Color(0.5, 1, 0.1));
    rightMaterial.set_diffuse(0.7);
    rightMaterial.set_specular(0.3);
  right->Material(rightMaterial);

  auto left = Sphere::New();
  left->Transform(translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33));
  Material leftMaterial;
    leftMaterial.set_color(Color(1, 0.8, 0.1));
    leftMaterial.set_diffuse(0.7);
    leftMaterial.set_specular(0.3);
  left->Material(leftMaterial);

    world.add_object(floor);
    world.add_object(leftWall);
    world.add_object(rightWall);
    world.add_object(middle);
    world.add_object(right);
    world.add_object(left);
    world.set_light(Light::New(point(-10, 10, -10), Color(1, 1, 1)));

  Camera camera(100, 50, M_PI/3);
    camera.set_transform(view_transform(point(0, 1.5, -5), point(0, 1, 0), Vector(0, 1, 0)));
  auto canvas = camera.render(world);
  
  std::ofstream outfile;
  outfile.open ("output.ppm");
  canvas.to_ppm_file(outfile);
  return 0;
}
