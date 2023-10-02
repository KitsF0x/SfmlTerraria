add_library(world STATIC "WorldGenerator.cpp")
target_include_directories(world PUBLIC .)
target_link_libraries(world PRIVATE blocks_game_objects)