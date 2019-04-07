#include <raytracer/material.h>

#include <cmath>

#include <raytracer/light.h>


//------------------------------------------------------------------------------
Material::Material()
    : color_{1, 1, 1}
      , ambient_(0.1)
      , diffuse_(0.9)
      , specular_(0.9)
      , shininess_(200.0)
{
}

//------------------------------------------------------------------------------
Material::Material(const class Color& a_color,
                   double a_ambient,
                   double a_diffuse,
                   double a_specular,
                   double a_shininess)
    : color_(a_color)
      , ambient_(a_ambient)
      , diffuse_(a_diffuse)
      , specular_(a_specular)
      , shininess_(a_shininess)
{
}

//------------------------------------------------------------------------------
bool Material::operator==(const Material& a_rhs) const
{
  return color_ == a_rhs.color_ && ambient_ == a_rhs.ambient_ &&
         diffuse_ == a_rhs.diffuse_ &&
         specular_ == a_rhs.specular_ && shininess_ == a_rhs.shininess_;
}

//------------------------------------------------------------------------------
Color Material::color() const
{
  return color_;
}

//------------------------------------------------------------------------------
void Material::set_color(const class Color& a_color)
{
  color_ = a_color;
}

//------------------------------------------------------------------------------
double Material::ambient() const
{
  return ambient_;
}

//------------------------------------------------------------------------------
void Material::set_ambient(double a_ambient)
{
  ambient_ = a_ambient;
}

//------------------------------------------------------------------------------
double Material::diffuse() const
{
  return diffuse_;
}

//------------------------------------------------------------------------------
void Material::set_diffuse(double a_diffuse)
{
  diffuse_ = a_diffuse;
}

//------------------------------------------------------------------------------
double Material::specular() const
{
  return specular_;
}

//------------------------------------------------------------------------------
void Material::set_specular(double a_specular)
{
  specular_ = a_specular;
}

//------------------------------------------------------------------------------
double Material::shininess() const
{
  return shininess_;
}

//------------------------------------------------------------------------------
void Material::set_shininess(double a_shininess)
{
  shininess_ = a_shininess;
}

//------------------------------------------------------------------------------
Color lighting(const Material& a_material,
               const Light& a_light,
               const Tuple& a_position,
               const Tuple& a_to_eye,
               const Tuple& a_normal)
{
  // combine the surface color with the light's set_color/intensity
  Color effective_color = a_material.color() * a_light.intensity();

  // find the direction to the light source
  Tuple to_light = (a_light.position() - a_position).normalize();

  // compute the ambient contribution
  Color ambient = effective_color * a_material.ambient();

  // light_dot_normal represents the cosine of the angle between the
  // light vector and the normal vector. A negative number means the
  // light is on the other side of the surface.
  double light_dot_normal = dot(to_light, a_normal);
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
    diffuse = effective_color * a_material.diffuse() * light_dot_normal;

    // reflect_dot_eye represents the cosine of the angle between the
    // reflection vector and the to_eye vector. A negative number means the
    // light reflects away from the to_eye.
    Tuple reflect_v = reflect(-to_light, a_normal);
    double reflect_dot_eye = dot(reflect_v, a_to_eye);
    if (reflect_dot_eye <= 0)
    {
      specular = black;
    }
    else
    {
      // compute the specular contribution
      double factor = pow(reflect_dot_eye, a_material.shininess());
      specular = a_light.intensity() * a_material.specular() * factor;
    }
  }

  // Add the three contributions together to get the final shading
  return ambient + diffuse + specular;
}
