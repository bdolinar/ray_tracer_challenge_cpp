
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
  floorMaterial.Color(Color(1, 0.9, 0.9));
  floorMaterial.Specular(0);

  auto floor = Sphere::New();
  floor->Transform(Scaling(10, 0.01, 10));
  floor->Material(floorMaterial);

  auto leftWall = Sphere::New();
  auto leftWallTransform = Translation(0, 0, 5) * RotationY(-M_PI_4) * RotationX(M_PI_2) * Scaling(10, 0.01, 10);
  leftWall->Transform(leftWallTransform);
  leftWall->Material(floorMaterial);

  auto rightWall = Sphere::New();
  auto rightWallTransform = Translation(0, 0, 5) * RotationY(M_PI_4) * RotationX(M_PI_2) * Scaling(10, 0.01, 10);
  rightWall->Transform(rightWallTransform);
  rightWall->Material(floorMaterial);

  auto middle = Sphere::New();
  middle->Transform(Translation(-0.5, 1, 0.5));
  Material middleMaterial;
  middleMaterial.Color(Color(0.1, 1, 0.5));
  middleMaterial.Diffuse(0.7);
  middleMaterial.Specular(0.3);
  middle->Material(middleMaterial);

  auto right = Sphere::New();
  right->Transform(Translation(1.5, 0.5, -0.5) * Scaling(0.5, 0.5, 0.5));
  Material rightMaterial;
  rightMaterial.Color(Color(0.5, 1, 0.1));
  rightMaterial.Diffuse(0.7);
  rightMaterial.Specular(0.3);
  right->Material(rightMaterial);

  auto left = Sphere::New();
  left->Transform(Translation(-1.5, 0.33, -0.75) * Scaling(0.33, 0.33, 0.33));
  Material leftMaterial;
  leftMaterial.Color(Color(1, 0.8, 0.1));
  leftMaterial.Diffuse(0.7);
  leftMaterial.Specular(0.3);
  left->Material(leftMaterial);

  world.AddObject(floor);
  world.AddObject(leftWall);
  world.AddObject(rightWall);
  world.AddObject(middle);
  world.AddObject(right);
  world.AddObject(left);
  world.AddLight(Light::New(Point(-10, 10, -10), Color(1, 1, 1)));

  Camera camera(100, 50, M_PI/3);
  camera.Transform(ViewTransform(Point(0, 1.5, -5), Point(0, 1, 0), Vector(0, 1, 0)));
  auto canvas = camera.Render(world);
  
  std::ofstream outfile;
  outfile.open ("output.ppm");
  canvas.ToPpmFile(outfile);
  return 0;
}
