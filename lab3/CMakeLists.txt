cmake_minimum_required(VERSION 3.28)
project(lab3)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_1-2
        1_2/main.cpp
        1_2/IBeverage.h
        1_2/Condiments.h
        1_2/Beverages.h
)
add_executable(${PROJECT_NAME}Test_1-2
        1_2/IBeverage.h
        1_2/Condiments.h
        1_2/Beverages.h
)

target_link_libraries(${PROJECT_NAME}Test_1-2 gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test_1-2 COMMAND ${PROJECT_NAME}Test_1-2)

