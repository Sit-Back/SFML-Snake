cmake_minimum_required(VERSION 3.31.6)
project(game-snake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -glldb")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -glldb")
set(CMAKE_BUILD_TYPE Debug)

find_package(SFML 3.0 COMPONENTS Graphics System Window REQUIRED)
file(GLOB_RECURSE SOURCE_FILES src/*.cpp)
add_executable(game-snake ${SOURCE_FILES})

target_include_directories(game-snake PRIVATE ${CMAKE_SOURCE_DIR}/include )

target_link_libraries(game-snake PRIVATE SFML::Graphics SFML::Window SFML::System)
