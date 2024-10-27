cmake_minimum_required(VERSION 3.28)
project(lab6)

set(CMAKE_CXX_STANDARD 23)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
        1/main.cpp
        1/graphics_lib.h
        1/shape_drawing_lib.h
        1/modern_graphics_lib.h
        1/ModernGraphicsAdapter.h
        1/ModernGraphicsClassAdapter.h
)
add_executable(${PROJECT_NAME}Test_1
        test/main.cpp
)

target_link_libraries(${PROJECT_NAME}Test_1 gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test_1 COMMAND ${PROJECT_NAME}Test_1)

