cmake_minimum_required(VERSION 3.0.0)
project(SfmlTerraria)

find_package(GTest CONFIG REQUIRED)
find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)

add_subdirectory(src)
add_subdirectory(test)
