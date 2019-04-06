include_directories(${CMAKE_SOURCE_DIR}/raytracer/raytracer)
include_directories(${CMAKE_CURRENT_LIST_DIR})

add_executable(run_tests
  main.cpp
  unit_tests/canvas_tests.cpp
  unit_tests/matrices_tests.cpp
  unit_tests/transformations_tests.cpp
  unit_tests/tuples_tests.cpp
)

target_link_libraries(run_tests raytracer ${Boost_LIBRARIES})
