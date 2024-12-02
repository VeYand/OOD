cmake_minimum_required(VERSION 3.28)
project(lab8)

set(CMAKE_CXX_STANDARD 23)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

option(CODE_COVERAGE "Enable code coverage" ON)
if (CODE_COVERAGE)
    if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "(Apple)?[Cc]lang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-instr-generate -fcoverage-mapping")
    else ()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage")
    endif ()
endif ()

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/CoW.h
        src/Drawer.h
        src/Drawer.cpp
        src/Geom.h
        src/Image.cpp
        src/Image.h
        src/Tile.h
)
add_executable(${PROJECT_NAME}Test
        test/main.cpp
)

target_link_libraries(${PROJECT_NAME}Test gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test COMMAND ${PROJECT_NAME}Test)
