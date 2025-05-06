cmake_minimum_required(VERSION 4.0.1)
project(game-snake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SFML 3.0 COMPONENTS Graphics System Window REQUIRED)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_executable(game-snake ${SOURCE_FILES})

target_include_directories(game-snake PRIVATE ${CMAKE_SOURCE_DIR}/include )

target_link_libraries(game-snake PRIVATE SFML::Graphics SFML::Window SFML::System)
