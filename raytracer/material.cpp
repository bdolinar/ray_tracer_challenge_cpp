#include <raytracer/material.h>

#include <math.h>

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
               const Tuple& eyev,
               const Tuple& normalv)
{
  // combine the surface color with the light's color/intensity
  Color effective_color = material.Color() * light.Intensity();

  // find the direction to the light source
  Tuple lightv = (light.Position() - position).Normalize();

  // compute the ambient contribution
  Color ambient = effective_color * material.Ambient();

  // light_dot_normal represents the cosine of the angle between the
  // light vector and the normal vector. A negative number means the
  // light is on the other side of the surface.
  double light_dot_normal = Dot(lightv, normalv);
  Color diffuse;
  Color specular;
  Color black(0, 0, 0);
  if (light_dot_normal < 0)
  {
    diffuse = black;
    specular = black;
  }
  else
  {
    // compute the diffuse contribution
    diffuse = effective_color * material.Diffuse() * light_dot_normal;

    // reflect_dot_eye represents the cosine of the angle between the
    // reflection vector and the eye vector. A negative number means the
    // light reflects away from the eye.
    Tuple reflectv = Reflect(-lightv, normalv);
    double reflect_dot_eye = Dot(reflectv, eyev);
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
