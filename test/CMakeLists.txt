project(tests)

if(WIN32 AND NOT ${CUSTOM_BOOST_PATH})
	find_package (Boost COMPONENTS unit_test_framework REQUIRED)
	include_directories(${Boost_INCLUDE_DIRS})
elseif(${CUSTOM_BOOST_PATH})
	include_directories(${CUSTOM_BOOST_PATH})
endif()

file(GLOB TESTS_SOURCE "*.cpp")

foreach(test ${TESTS_SOURCE})
	get_filename_component(test_name ${test} NAME_WE)

	add_executable(${test_name} ${test})
	set_target_properties(${test_name} PROPERTIES PREFIX "" COMPILE_FLAGS "-m32" LINK_FLAGS "-m32" POSITION_INDEPENDENT_CODE ON)
	target_link_libraries(${test_name} building_amxx_static)

	add_test(NAME ${test_name} COMMAND ${test_name})
endforeach()

