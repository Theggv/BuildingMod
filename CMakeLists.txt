cmake_minimum_required (VERSION 3.8)

project (building_amxx VERSION 1.0.0 LANGUAGES CXX)
set(PROJECT building_amxx)

set(CMAKE_CXX_STANDARD 17)

# Include default stuff
include(GNUInstallDirs)

# Boost setup

add_subdirectory(external/boost-cmake)

# Dependencies
set(CMAKE_INCLUDE_PATH
	"external"
	"external/metamod"
	"external/cssdk/common"
	"external/cssdk/dlls"
	"external/cssdk/engine"
	"external/cssdk/game_shared"
	"external/cssdk/pm_shared"
	"external/cssdk/public"
	"src"
)

add_definitions(
	-D_CRT_SECURE_NO_WARNINGS
	-DHAVE_STRONG_TYPEDEF
	-DNO_MSVC8_AUTO_COMPAT
	-DHAVE_STDINT_H
	-D_DEBUG
	-D_MBCS
)

include_directories(
	${CMAKE_INCLUDE_PATH}
	${CMAKE_BINARY_DIR}/_deps/boost-src
)

# Src
add_subdirectory(src)

# Tests
include(CTest)
enable_testing()

add_subdirectory(test)
