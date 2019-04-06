
#pragma once

#include "color.h"
#include "tuple.h"

class Light
{
public:
  /// \brief Construct a light.
  /// \param[in] position The position of the light in world space.
  /// \param[in] intensity The brightness and color of the light.
  Light(const Tuple& position, const Color& intensity);

  /// \brief Get the world space position of the light.
  /// \return The world space position of the light.
  const Tuple& Position() const;

  /// \brief Get the intensity of the light.
  /// \return The intensity of the light.
  const Color& Intensity() const;

private:
  Tuple position_;  ///< The position of the light in world space.
  Color intensity_; ///< The intensity and color of the light.
};
