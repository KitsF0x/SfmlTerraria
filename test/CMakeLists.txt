add_executable(${PROJECT_NAME}-ut
	"PlayerTest.cpp"
	"AGameObjectTest.cpp"
	"GameObjectsManagerTest.cpp"
	"WorldGeneraionTest.cpp"
)

target_link_libraries(${PROJECT_NAME}-ut PRIVATE 
	GTest::gtest 
	GTest::gtest_main
	
	base_game_object
	blocks_game_objects
	player_game_object
	world
)