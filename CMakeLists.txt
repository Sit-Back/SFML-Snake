cmake_minimum_required(VERSION 4.0.1)
project(sfml-snake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 3.0 COMPONENTS Graphics System Window REQUIRED)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_executable(sfml-snake ${SOURCE_FILES})

target_include_directories( sfml-snake PRIVATE ${CMAKE_SOURCE_DIR}/src )

target_link_libraries(sfml-snake PRIVATE SFML::Graphics SFML::Window SFML::System)
