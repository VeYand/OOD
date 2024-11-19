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

add_executable(${PROJECT_NAME}
        src/gumball_machine/GumBallMachineWithDynamicallyCreatedState.h
        src/gumball_machine/GumBallMachineWithState.h
        src/main.cpp
        src/gumball_machine/NaiveGumBallMachine.h
)
add_executable(${PROJECT_NAME}Test_1
        test/main.cpp
        test/test.cpp
)

target_link_libraries(${PROJECT_NAME}Test_1 gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test_1 COMMAND ${PROJECT_NAME}Test_1)

