
# Get all cpp files in current directory
file (GLOB COMMON_SRC
	"*.cpp"
	"module/*.cpp"
	"module/sdk/*.cpp"
)

file (GLOB COMMON_HEADERS
	"*.h"
	"module/*.h"
	"module/sdk/*h"
)

set (SRC ${COMMON_SRC})

set (SRC_DIRS
	"./module"
)

set (SOME_SHEET 
	"${PROJECT_SOURCE_DIR}/deps/cssdk/public/interface.cpp"
)

if (UNIX)
	message("Platform: Linux")
	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-exceptions -std=c++11")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -Wl,--no-as-needed")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -ggdb -O3 -Wall -ffunction-sections -fdata-sections")
	## Produce code optimized for the most common IA32/AMD64/EM64T processors.
	## As new processors are deployed in the marketplace, the behavior of this option will change.
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
		-mtune=generic -msse3\
		-Wno-write-strings -Wno-invalid-offsetof\
		-Wno-unused-variable -Wno-unused-function\
		-Wno-unused-result -Wno-invalid-offsetof\
		-fpermissive -Wno-switch -Wno-enum-compare\
		-Wno-unknown-pragmas -Wno-unused-value")
	
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}\
		-Wno-unused-local-typedefs\
		-Wno-sign-compare\
		-Wno-strict-aliasing\
		-Wno-unused-but-set-variable\
		-fno-devirtualize")

else()
	message("Platform: Windows")
endif()

# Setup shared library
# set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wall -Wl,--kill-at")

add_library(${PROJECT} SHARED ${COMMON_HEADERS} ${SRC} ${SOME_SHEET} "BuildingMod.def")
target_compile_features(${PROJECT} PRIVATE cxx_std_14)
set_target_properties(${PROJECT} PROPERTIES PREFIX "" COMPILE_FLAGS "-m32" LINK_FLAGS "-m32" POSITION_INDEPENDENT_CODE ON)

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

	target_link_libraries(${PROJECT} dl)
endif()
