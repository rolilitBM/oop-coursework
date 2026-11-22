cmake_minimum_required(VERSION 3.15)
project(oop_coursework)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
endif()

add_executable(oop_coursework
    main.cpp
    image.cpp
    image.hpp
    project.cpp
    project.hpp
    source_file.cpp
    source_file.hpp
)
