add_subdirectory(game_objects)
add_subdirectory(world)

add_executable(${PROJECT_NAME} 
	"main.cpp"
)
target_link_libraries(${PROJECT_NAME} PUBLIC
	sfml-graphics
	sfml-window

	base_game_object
	player_game_object
	blocks_game_objects
	world
)
