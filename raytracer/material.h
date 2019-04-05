
#pragma once

#include <raytracer/color.h>

class Light;
class Tuple;

/// Material for a raytraced object.
class Material
{
public:
  /// \brief Construct a default material.
  Material();

  /// \brief Construct a material.
  /// \param color The material color.
  /// \param ambient The amount of ambient light (0.0 to 1.0).
  /// \param diffuse The amount of diffuse light (0.0 to 1.0).
  /// \param specular The amount of specular light (0.0 to 1.0).
  /// \param shininess The shininess of the material.
  Material(const class Color& color,
           double ambient,
           double diffuse,
           double specular,
           double shininess);

  /// \brief Equals operator.
  /// \param rhs The object to compare against.
  /// \return True if the objects are equal.
  bool operator==(const Material& rhs) const;

  /// \brief Get the material color.
  /// \return The material color.
  Color Color() const;

  /// \brief Set the material color.
  /// \param color The material color.
  void Color(const class Color& color);

  /// \brief Get the ambient value (amount of ambient light).
  /// \return The ambient value.
  double Ambient() const;

  /// \brief Set the ambient value (amount of ambient light).
  /// \param ambient The ambient value.
  void Ambient(double ambient);

  /// \brief Get the diffuse value (light reflected from surface).
  /// \return The diffuse value.
  double Diffuse() const;

  /// \brief Set the diffuse value (light reflected from surface).
  /// \param diffuse The diffuse value.
  void Diffuse(double diffuse);

  /// \brief Get the specular value (amount of specular light 0.0 - 1.0).
  /// \return The specular value.
  double Specular() const;

  /// \brief Set the specular value (how shiny).
  /// \param specular The specular value.
  void Specular(double specular);

  /// \brief Get the shininess value (size of shiny spot).
  /// \return The shininess value.
  double Shininess() const;

  /// \brief Set the shininess value (size of shiny spot).
  /// \param shininess The shininess value.
  void Shininess(double shininess);

private:
  class Color color_; ///< Color of the material.
  double ambient_;    ///< Amount of ambient light (0.0 to 1.0).
  double diffuse_;    ///< Amount of diffuse light (0.0 to 1.0).
  double specular_;   ///< Amount of specular light (0.0 to 1.0).
  double shininess_;  ///< Specular shininess.
};

/// \brief Calculate the lighting color for an intersection.
/// \param m The material at the intersection.
/// \param light The light at the intersection.
/// \param position The point of the intersection.
/// \param toEye Vector to the eye at the intersection.
/// \param normal Normal at the surface for the intersection.
/// \return The resulting color at the intersection.
Color Lighting(const Material& m,
               const Light& light,
               const Tuple& position,
               const Tuple& toEye,
               const Tuple& normal);
