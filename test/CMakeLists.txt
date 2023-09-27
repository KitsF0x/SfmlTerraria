add_executable(${PROJECT_NAME}-ut
	"SimpleTest.cpp"
	"PlayerTest.cpp"
)

target_link_libraries(${PROJECT_NAME}-ut PRIVATE 
	GTest::gtest 
	GTest::gtest_main
	
	player
)