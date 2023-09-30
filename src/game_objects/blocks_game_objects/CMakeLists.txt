add_library(blocks_game_objects STATIC
	"GrassBlock.cpp"
 "SandBlock.cpp" "WaterBlock.cpp")
target_include_directories(blocks_game_objects PUBLIC .)
target_link_libraries(blocks_game_objects PUBLIC 
	base_game_object
)