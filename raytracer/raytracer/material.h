
#pragma once

#include "color.h"

class Light;
class Tuple;

class Material
{
public:
  /// \brief Construct a default material.
  Material();

  /// \brief Construct a material.
  /// \param[in] color The material color.
  /// \param[in] ambient The ambient value.
  /// \param[in] specular The specular value.
  /// \param[in] shininess The shininess value.
  Material(const class Color& color,
           double ambient,
           double diffuse,
           double specular,
           double shininess);

  bool operator==(const Material& rhs) const;

  /// \brief Get the material color.
  /// \return The material color.
  Color Color() const;

  /// \brief Set the material color.
  /// \param[in] color The material color.
  void Color(const class Color& color);

  /// \brief Get the ambient value (amount of ambient light).
  /// \return The ambient value.
  double Ambient() const;

  /// \brief Set the ambient value (amount of ambient light).
  /// \param[in] ambient The ambient value.
  void Ambient(double ambient);

  /// \brief Get the diffuse value (light reflected from surface).
  /// \return The diffuse value.
  double Diffuse() const;

  /// \brief Set the diffuse value (light reflected from surface).
  /// \param[in] diffuse The diffuse value.
  void Diffuse(double diffuse);

  /// \brief Get the specular value (amount of specular light 0.0 - 1.0).
  /// \return The specular value.
  double Specular() const;

  /// \brief Set the specular value (how shiny).
  /// \param[in] specular The specular value.
  void Specular(double specular);

  /// \brief Get the shininess value (size of shiney spot).
  /// \return The shininess value.
  double Shininess() const;

  /// \brief Set the shininess value (size of shiney spot).
  /// \param[in] shininess The shininess value.
  void Shininess(double shininess);

private:
  class Color color_;
  double ambient_;
  double diffuse_;
  double specular_;
  double shininess_;
};

Color Lighting(const Material& m,
               const Light& light,
               const Tuple& position,
               const Tuple& eyev,
               const Tuple& normalv);
