cmake_minimum_required(VERSION 3.12.4)
project(ray_tracer_challenge_cpp)

set(CMAKE_CXX_STANDARD 14)

include_directories(${CMAKE_CURRENT_LIST_DIR} libraries)

# raytracer library
set(raytracer_sources
        raytracer/camera.cpp
        raytracer/canvas.cpp
        raytracer/color.cpp
        raytracer/intersection.cpp
        raytracer/light.cpp
        raytracer/material.cpp
        raytracer/matrix.cpp
        raytracer/ray.cpp
        raytracer/sphere.cpp
        raytracer/test_utils.cpp
        raytracer/transform.cpp
        raytracer/tuple.cpp
        raytracer/world.cpp
        )

set(raytracer_headers
        raytracer/camera.h
        raytracer/canvas.h
        raytracer/color.h
        raytracer/intersection.h
        raytracer/light.h
        raytracer/material.h
        raytracer/matrix.h
        raytracer/ray.h
        raytracer/sphere.h
        raytracer/test_utils.h
        raytracer/transform.h
        raytracer/tuple.h
        raytracer/world.h
        )

add_library(raytracer ${raytracer_sources} ${raytracer_headers})

# test executable
set(test_sources
        tests/main.cpp
        tests/camera_tests.cpp
        tests/canvas_tests.cpp
        tests/intersections_tests.cpp
        tests/lights_tests.cpp
        tests/materials_tests.cpp
        tests/matrices_tests.cpp
        tests/rays_tests.cpp
        tests/spheres_tests.cpp
        tests/transformations_tests.cpp
        tests/tuples_tests.cpp
        tests/world_tests.cpp)

add_executable(run_tests ${test_sources})
target_link_libraries(run_tests raytracer)

add_executable(chapter_5 chapter_5/chapter_5_main.cpp)
target_link_libraries(chapter_5 raytracer)

add_executable(chapter_6 chapter_6/chapter_6_main.cpp)
target_link_libraries(chapter_6 raytracer)

add_executable(chapter_7 chapter_7/chapter_7_main.cpp)
target_link_libraries(chapter_7 raytracer)
