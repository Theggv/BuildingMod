include(GoogleTest)
include(CTest)
include(FetchContent)

add_subdirectory(math)
include_directories(../build/_deps/googletest-src/googletest/include)

add_executable(tests_main main.cpp)