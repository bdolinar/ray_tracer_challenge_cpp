
#pragma once

#include <memory>

#include <raytracer/color.h>
#include <raytracer/tuple.h>


/// A point light source.
class Light
{
public:
  /// Construct a Light as a shared pointer.
  /// \param a_position The position of the light in world space.
  /// \param a_intensity The brightness and color of the light.
  /// \return The Light shared pointer.
  static std::shared_ptr<Light>
  new_ptr(const Tuple& a_position, const Color& a_intensity);

  /// Construct a light.
  /// \param a_position The position of the light in world space.
  /// \param a_intensity The brightness and color of the light.
  Light(const Tuple& a_position, const Color& a_intensity);

  /// Get the world space position of the light.
  /// \return The world space position of the light.
  const Tuple& position() const;

  /// Get the intensity of the light.
  /// \return The intensity of the light.
  const Color& intensity() const;

private:
  Tuple position_;  ///< The position of the light in world space.
  Color intensity_; ///< The intensity and color of the light.
};
