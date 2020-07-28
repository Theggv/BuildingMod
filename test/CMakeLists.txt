project(tests)

find_package (Boost COMPONENTS unit_test_framework REQUIRED)

if(NOT ${Boost_FOUND})
	message("Boost was not found" FATAL_ERROR)
else()
	include_directories(${Boost_INCLUDE_DIRS})
endif()

set(test1_source main.cpp)

add_executable(test1 ${SRC} ${test1_source})

target_link_libraries(test1 ${Boost_LIBRARIES} building_amxx)

add_test(NAME test1 COMMAND test1)
