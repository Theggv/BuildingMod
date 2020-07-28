project(tests)

find_package (Boost COMPONENTS unit_test_framework REQUIRED)

if(NOT ${Boost_FOUND})
	message("Boost was not found" FATAL_ERROR)
else()
	include_directories(${Boost_INCLUDE_DIRS})
endif()

file(GLOB TESTS_SOURCE "*.cpp")

message("Tests source: ${TESTS_SOURCE}")

foreach(test ${TESTS_SOURCE})
	get_filename_component(test_name ${test} NAME_WE)
	message("Current test: ${test_name}")

	add_executable(${test_name} ${test})
	target_link_libraries(${test_name} ${Boost_LIBRARIES} building_amxx_static)
	add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

