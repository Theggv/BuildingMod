file(GLOB_RECURSE TESTS_SOURCE "*.cpp")

add_definitions(-DBOOST_TEST_NO_LIB)
add_executable(GameTests ${TESTS_SOURCE})

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	set_target_properties(GameTests PROPERTIES PREFIX "" COMPILE_FLAGS "-m32" LINK_FLAGS "-m32" POSITION_INDEPENDENT_CODE ON)
endif()

target_link_libraries(GameTests building_amxx_static)

add_test(
	NAME
		GameTests 
	COMMAND
		GameTests
)

