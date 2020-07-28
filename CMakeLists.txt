# CMakeList.txt: проект CMake для BuildingMod; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.13)

# THIS HAS TO COME BEFORE THE PROJECT LINE
# set(CMAKE_C_COMPILER "/usr/lib/gcc")
# set(CMAKE_CXX_COMPILER "/usr/lib/g++")
# THIS HAS TO COME BEFORE THE PROJECT LINE

project (building_amxx VERSION 1.0.0 LANGUAGES CXX)
set(PROJECT building_amxx)

# Include default stuff
include(GNUInstallDirs)

# Dependencies
set(CMAKE_INCLUDE_PATH
	"./deps"
	"./deps/boost"
	"./deps/metamod"
	"./deps/cssdk/common"
	"./deps/cssdk/dlls"
	"./deps/cssdk/engine"
	"./deps/cssdk/game_shared"
	"./deps/cssdk/pm_shared"
	"./deps/cssdk/public"
	"./BuildingMod"
)

include_directories(
	${CMAKE_INCLUDE_PATH}
	${GTEST_INCLUDE_DIRS}
)

add_definitions(
	-D_CRT_SECURE_NO_WARNINGS
	-DHAVE_STRONG_TYPEDEF
	-DNO_MSVC8_AUTO_COMPAT
	-DHAVE_STDINT_H
	-D_DEBUG
	-D_MBCS
)

# Gtest
# Download and unpack googletest at configure time
configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "CMake step for googletest failed: ${result}")
endif()
execute_process(COMMAND ${CMAKE_COMMAND} --build .
  RESULT_VARIABLE result
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/googletest-download )
if(result)
  message(FATAL_ERROR "Build step for googletest failed: ${result}")
endif()

# Prevent overriding the parent project's compiler/linker
# settings on Windows
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Add googletest directly to our build. This defines
# the gtest and gtest_main targets.
add_subdirectory(${CMAKE_CURRENT_BINARY_DIR}/googletest-src
                 ${CMAKE_CURRENT_BINARY_DIR}/googletest-build
                 EXCLUDE_FROM_ALL)

# The gtest/gtest_main targets carry header search path
# dependencies automatically when using CMake 2.8.11 or
# later. Otherwise we have to add them here ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
  include_directories("${gtest_SOURCE_DIR}/include")
endif()



# Src
add_subdirectory(BuildingMod)

# Now simply link against gtest or gtest_main as needed. Eg
target_link_libraries(${PROJECT} gtest_main)
add_test(NAME example_test COMMAND example)