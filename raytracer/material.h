
#pragma once

#include <raytracer/color.h>


class Light;

class Tuple;

/// Material for a ray traced object.
class Material
{
public:
  /// Construct a default material.
  Material();

  /// Construct a material.
  /// \param a_color The material color.
  /// \param a_ambient The amount of ambient light (0.0 to 1.0).
  /// \param a_diffuse The amount of diffuse light (0.0 to 1.0).
  /// \param a_specular The amount of specular light (0.0 to 1.0).
  /// \param a_shininess The shininess of the material.
  Material(const class Color& a_color,
           double a_ambient,
           double a_diffuse,
           double a_specular,
           double a_shininess);

  /// Equals operator.
  /// \param a_rhs The object to compare against.
  /// \return True if the objects are equal.
  bool operator==(const Material& a_rhs) const;

  /// Get the material color.
  /// \return The material color.
  Color color() const;

  /// Set the material color.
  /// \param a_color The material color.
  void set_color(const class Color& a_color);

  /// Get the ambient value (amount of ambient light).
  /// \return The ambient value.
  double ambient() const;

  /// Set the ambient value (amount of ambient light).
  /// \param a_ambient The ambient value.
  void set_ambient(double a_ambient);

  /// Get the diffuse value (light reflected from surface).
  /// \return The diffuse value.
  double diffuse() const;

  /// Set the diffuse value (light reflected from surface).
  /// \param a_diffuse The diffuse value.
  void set_diffuse(double a_diffuse);

  /// Get the specular value (amount of specular light 0.0 - 1.0).
  /// \return The specular value.
  double specular() const;

  /// Set the specular value (how shiny).
  /// \param a_specular The specular value.
  void set_specular(double a_specular);

  /// Get the shininess value (size of shiny spot).
  /// \return The shininess value.
  double shininess() const;

  /// Set the shininess value (size of shiny spot).
  /// \param a_shininess The shininess value.
  void set_shininess(double a_shininess);

private:
  class Color color_; ///< Color of the material.
  double ambient_;    ///< Amount of ambient light (0.0 to 1.0).
  double diffuse_;    ///< Amount of diffuse light (0.0 to 1.0).
  double specular_;   ///< Amount of specular light (0.0 to 1.0).
  double shininess_;  ///< Specular shininess.
};

/// Calculate the lighting color for an intersection.
/// \param a_material The material at the intersection.
/// \param light The light at the intersection.
/// \param a_position The point of the intersection.
/// \param a_to_eye Vector to the eye at the intersection.
/// \param a_normal Normal at the surface for the intersection.
/// \return The resulting color at the intersection.
Color lighting(const Material& a_material,
               const Light& a_light,
               const Tuple& a_position,
               const Tuple& a_to_eye,
               const Tuple& a_normal);
