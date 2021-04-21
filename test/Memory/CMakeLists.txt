file(GLOB_RECURSE TESTS_SOURCE "*.cpp")

add_executable(MemoryTests ${TESTS_SOURCE})

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	set_target_properties(MemoryTests PROPERTIES PREFIX "" COMPILE_FLAGS "-m32" LINK_FLAGS "-m32" POSITION_INDEPENDENT_CODE ON)
endif()

target_link_libraries(MemoryTests building_amxx_static)

add_test(
	NAME
		MemoryTests 
	COMMAND
		MemoryTests
)

