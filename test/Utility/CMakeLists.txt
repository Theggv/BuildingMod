file(GLOB_RECURSE TESTS_SOURCE "*.cpp")

add_executable(UtilityTests ${TESTS_SOURCE})

if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU")
	set_target_properties(UtilityTests PROPERTIES PREFIX "" COMPILE_FLAGS "-m32" LINK_FLAGS "-m32" POSITION_INDEPENDENT_CODE ON)
endif()

target_link_libraries(UtilityTests building_amxx_static)

add_test(
	NAME
		UtilityTests 
	COMMAND
		${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}/UtilityTests
)

