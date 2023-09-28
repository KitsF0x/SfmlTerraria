add_library(player STATIC 
	"Player.cpp"
	"GravityManager.cpp"
)
target_include_directories(player PUBLIC .)
target_link_libraries(player PUBLIC sfml-graphics sfml-window)