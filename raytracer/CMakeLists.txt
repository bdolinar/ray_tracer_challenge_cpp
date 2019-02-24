include_directories(${CMAKE_CURRENT_LIST_DIR})

set(raytracer_headers
  raytracer/canvas.h
  raytracer/color.h
  raytracer/intersection.h
  raytracer/light.h
  raytracer/material.h
  raytracer/matrix.h
  raytracer/ray.h
  raytracer/sphere.h
  raytracer/transform.h
  raytracer/tuple.h
)

set(raytracer_sources
  raytracer/canvas.cpp
  raytracer/color.cpp
  raytracer/intersection.cpp
  raytracer/light.cpp
  raytracer/material.cpp
  raytracer/matrix.cpp
  raytracer/ray.cpp
  raytracer/sphere.cpp
  raytracer/transform.cpp
  raytracer/tuple.cpp
)

add_library(raytracer ${raytracer_sources} ${raytracer_headers})
