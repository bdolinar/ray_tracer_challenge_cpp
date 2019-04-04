#include <raytracer/material.h>

#include <cmath>

#include <raytracer/light.h>

Material::Material()
: color_{1, 1, 1}
, ambient_(0.1)
, diffuse_(0.9)
, specular_(0.9)
, shininess_(200.0)
{
}


Material::Material(const class Color& color,
                   double ambient,
                   double diffuse,
                   double specular,
                   double shininess)
: color_(color)
, ambient_(ambient)
, diffuse_(diffuse)
, specular_(specular)
, shininess_(shininess)
{
}


bool Material::operator==(const Material& rhs) const
{
  return color_ == rhs.color_ && ambient_ == rhs.ambient_ && diffuse_ == rhs.diffuse_ &&
         specular_ == rhs.specular_ && shininess_ == rhs.shininess_;
}


Color Material::Color() const
{
  return color_;
}


void Material::Color(const class Color& color)
{
  color_ = color;
}


double Material::Ambient() const
{
  return ambient_;
}


void Material::Ambient(double ambient)
{
  ambient_ = ambient;
}


double Material::Diffuse() const
{
  return diffuse_;
}


void Material::Diffuse(double diffuse)
{
  diffuse_ = diffuse;
}


double Material::Specular() const
{
  return specular_;
}


void Material::Specular(double specular)
{
  specular_ = specular;
}


double Material::Shininess() const
{
  return shininess_;
}


void Material::Shininess(double shininess)
{
  shininess_ = shininess;
}


Color Lighting(const Material& material,
               const Light& light,
               const Tuple& position,
               const Tuple& toEye,
               const Tuple& normal)
{
  // combine the surface color with the light's color/intensity
  Color effectiveColor = material.Color() * light.Intensity();

  // find the direction to the light source
  Tuple lightv = (light.Position() - position).Normalize();

  // compute the ambient contribution
  Color ambient = effectiveColor * material.Ambient();

  // lightDotNormal represents the cosine of the angle between the
  // light vector and the normal vector. A negative number means the
  // light is on the other side of the surface.
  double lightDotNormal = Dot(lightv, normal);
  Color diffuse;
  Color specular;
  Color black(0, 0, 0);
  if (lightDotNormal < 0)
  {
    diffuse = black;
    specular = black;
  }
  else
  {
    // compute the diffuse contribution
    diffuse = effectiveColor * material.Diffuse() * lightDotNormal;

    // reflect_dot_eye represents the cosine of the angle between the
    // reflection vector and the toEye vector. A negative number means the
    // light reflects away from the toEye.
    Tuple reflectv = Reflect(-lightv, normal);
    double reflect_dot_eye = Dot(reflectv, toEye);
    if (reflect_dot_eye <= 0)
    {
      specular = black;
    }
    else
    {
      // compute the specular contribution
      double factor = pow(reflect_dot_eye, material.Shininess());
      specular = light.Intensity() * material.Specular() * factor;
    }
  }

  // Add the three contributions together to get the final shading
  return ambient + diffuse + specular;
}
