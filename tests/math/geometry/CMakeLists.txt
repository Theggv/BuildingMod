file(GLOB_RECURSE TESTS_SOURCE "*.cpp")

if (TESTS_SOURCE STREQUAL "")
	return()
endif()

add_executable(MathGeometryTests ${TESTS_SOURCE})

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	set_target_properties(MathGeometryTests PROPERTIES PREFIX "" COMPILE_FLAGS "-m32" LINK_FLAGS "-m32" POSITION_INDEPENDENT_CODE ON)
endif()

target_link_libraries(MathGeometryTests building_amxx_static)

add_test(
	NAME
		MathGeometryTests 
	COMMAND
		MathGeometryTests
)

