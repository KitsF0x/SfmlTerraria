add_library(player_game_object STATIC
	"Player.cpp"
)

target_include_directories(player_game_object PUBLIC .)
target_link_libraries(player_game_object PUBLIC 
	base_game_object
	blocks_game_objects
)