add_library(base_game_object STATIC
	"AGameObject.cpp"
	"GravityManager.cpp"
 "GameObjectsManager.cpp")

target_include_directories(base_game_object PUBLIC .)
target_link_libraries(base_game_object PUBLIC 
	sfml-graphics
	sfml-system
)