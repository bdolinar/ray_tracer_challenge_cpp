include_directories(${CMAKE_CURRENT_LIST_DIR})

set(raytracer_headers
  raytracer/canvas.h
  raytracer/color.h
  raytracer/tuple.h
)

set(raytracer_sources
  raytracer/canvas.cpp
  raytracer/color.cpp
  raytracer/tuple.cpp
)

add_library(raytracer ${raytracer_sources} ${raytracer_headers})
