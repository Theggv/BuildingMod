# Get all cpp files in current directory
file (GLOB COMMON_SRC
	"*.cpp"
	"module/*.cpp"
	"module/sdk/*.cpp"
	"module/natives/*.cpp"

	"game/*.cpp"
	"game/BuildSystem/*.cpp"
	"game/BuildSystem/BuildObjects/*.cpp"
	"game/Utility/*.cpp"
)

file (GLOB COMMON_HEADERS
	"*.h"
	"module/*.h"
	"module/sdk/*.h"
	"module/natives/*.h"

	"game/*.h"
	"game/BuildSystem/*.h"
	"game/BuildSystem/BuildObjects/*.h"
	"game/Utility/*.h"
)

set (SRC ${COMMON_SRC})

set (SRC_DIRS
	"./module"
	"./game"
)

set (SRC_DEPS 
	"${PROJECT_SOURCE_DIR}/deps/cssdk/public/interface.cpp"
)

if (UNIX)
	message("Platform: Linux")
	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -std=c++11")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -Wl,--no-as-needed")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -ggdb -O3 -ffunction-sections -fdata-sections")

	## Produce code optimized for the most common IA32/AMD64/EM64T processors.
	## As new processors are deployed in the marketplace, the behavior of this option will change.
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
	#	-mtune=generic -msse3\
	#	-Wno-write-strings -Wno-invalid-offsetof\
	#	-Wno-unused-variable -Wno-unused-function\
	#	-Wno-unused-result -Wno-invalid-offsetof\
	#	-fpermissive -Wno-switch -Wno-enum-compare\
	#	-Wno-unknown-pragmas -Wno-unused-value")
	
	# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
	#	-Wno-unused-local-typedefs\
	#	-Wno-sign-compare\
	#	-Wno-strict-aliasing\
	#	-Wno-unused-but-set-variable\
	#	-fno-devirtualize")

else()
	message("Platform: Windows")
endif()

# Setup shared library

add_library(${PROJECT} SHARED ${COMMON_HEADERS} ${SRC} ${SRC_DEPS} "BuildingMod.def")
target_include_directories(${PROJECT} PUBLIC ${SRC_DIRS})

if(UNIX)
	target_compile_definitions(${PROJECT} PUBLIC 
		-DUNICODE_FIXES
		-DUSE_QSTRING
		-DGNUC
		-DPOSIX
		-D_LINUX
		-DLINUX
		-D_stricmp=strcasecmp
		-D_strnicmp=strncasecmp
		-D_strdup=strdup
		-D_unlink=unlink
		-D_vsnprintf=vsnprintf
		-D_write=write
		-D_close=close
		-D_access=access
		-D_vsnwprintf=vswprintf
	)

	set_target_properties(${PROJECT} PROPERTIES PREFIX "" COMPILE_FLAGS "-m32" LINK_FLAGS "-m32" POSITION_INDEPENDENT_CODE ON)
	target_link_libraries(${PROJECT} dl)
	set_property(TARGET ${PROJECT} PROPERTY LIBRARY_OUTPUT_NAME building_amxx_i386)
endif()

#Setup static library

add_library(building_amxx_static STATIC ${COMMON_HEADERS} ${SRC} ${SRC_DEPS} "BuildingMod.def")
target_include_directories(building_amxx_static PUBLIC ${SRC_DIRS})

if(UNIX)
	target_compile_definitions(building_amxx_static PUBLIC 
		-DUNICODE_FIXES
		-DUSE_QSTRING
		-DGNUC
		-DPOSIX
		-D_LINUX
		-DLINUX
		-D_stricmp=strcasecmp
		-D_strnicmp=strncasecmp
		-D_strdup=strdup
		-D_unlink=unlink
		-D_vsnprintf=vsnprintf
		-D_write=write
		-D_close=close
		-D_access=access
		-D_vsnwprintf=vswprintf
	)

	set_target_properties(building_amxx_static PROPERTIES PREFIX "" COMPILE_FLAGS "-m32" LINK_FLAGS "-m32" POSITION_INDEPENDENT_CODE ON)
	set_property(TARGET building_amxx_static PROPERTY LIBRARY_OUTPUT_NAME building_amxx_i386_static)
endif()
