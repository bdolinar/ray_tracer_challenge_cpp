include_directories(SYSTEM ${CMAKE_SOURCE_DIR}/raytracer)
include_directories(SYSTEM ${CMAKE_CURRENT_LIST_DIR})

add_executable(run_tests
  main.cpp
  unit_tests/tuples_tests.cpp
  unit_tests/canvas_tests.cpp
)

target_link_libraries(run_tests raytracer ${Boost_LIBRARIES})
