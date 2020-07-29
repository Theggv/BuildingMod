# CMakeList.txt: проект CMake для BuildingMod; включите исходный код и определения,
# укажите здесь логику для конкретного проекта.
#
cmake_minimum_required (VERSION 3.8)

# THIS HAS TO COME BEFORE THE PROJECT LINE
# set(CMAKE_C_COMPILER "/usr/lib/gcc")
# set(CMAKE_CXX_COMPILER "/usr/lib/g++")
# THIS HAS TO COME BEFORE THE PROJECT LINE

project (building_amxx VERSION 1.0.0 LANGUAGES CXX)
set(PROJECT building_amxx)

set(CMAKE_CXX_STANDARD 17)

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

add_definitions(
	-D_CRT_SECURE_NO_WARNINGS
	-DHAVE_STRONG_TYPEDEF
	-DNO_MSVC8_AUTO_COMPAT
	-DHAVE_STDINT_H
	-D_DEBUG
	-D_MBCS
)

if(WIN32)
	find_package(Boost REQUIRED)
	include_directories(${Boost_INCLUDE_DIRS})
endif()

# message(Boost dirs: ${Boost_LIBRARY_DIRS})

include_directories(
	${CMAKE_INCLUDE_PATH}
)

include(CTest)
enable_testing()

# Src
add_subdirectory(BuildingMod)
add_subdirectory(test)