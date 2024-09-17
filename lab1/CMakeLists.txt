cmake_minimum_required(VERSION 3.28)
project(lab1)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_1
        1_1/lib/Duck/Fly/FlyNoWay.h
        1_1/lib/Duck/Fly/FlyWithWings.h
        1_1/lib/Duck/Fly/IFlyBehavior.h
        1_1/lib/Duck/Quack/IQuackBehavior.h
        1_1/lib/Duck/Quack/MuteQuackBehavior.h
        1_1/lib/Duck/Quack/QuackBehavior.h
        1_1/lib/Duck/Quack/SqueakBehavior.h
        1_1/lib/Duck/DecoyDuck.h
        1_1/lib/Duck/Duck.h
        1_1/lib/Duck/MallardDuck.h
        1_1/lib/Duck/ModelDuck.h
        1_1/lib/Duck/RedheadDuck.h
        1_1/lib/Duck/RubberDuck.h
        1_1/lib/DuckFunctions.h
        1_1/SimUDuck.cpp
        1_1/lib/Duck/Dance/DanceMinuetBehavior.h
        1_1/lib/Duck/Dance/DanceWaltzBehavior.h
        1_1/lib/Duck/Dance/IDanceBehavior.h
        1_1/lib/Duck/Dance/NoDanceBehavior.h
)

add_executable(${PROJECT_NAME}Test_1
        1_1/lib/Duck/Fly/FlyNoWay.h
        1_1/lib/Duck/Fly/FlyWithWings.h
        1_1/lib/Duck/Fly/IFlyBehavior.h
        1_1/lib/Duck/Quack/IQuackBehavior.h
        1_1/lib/Duck/Quack/MuteQuackBehavior.h
        1_1/lib/Duck/Quack/QuackBehavior.h
        1_1/lib/Duck/Quack/SqueakBehavior.h
        1_1/lib/Duck/DecoyDuck.h
        1_1/lib/Duck/Duck.h
        1_1/lib/Duck/MallardDuck.h
        1_1/lib/Duck/ModelDuck.h
        1_1/lib/Duck/RedheadDuck.h
        1_1/lib/Duck/RubberDuck.h
        1_1/lib/DuckFunctions.h
        1_1/lib/Duck/Dance/DanceMinuetBehavior.h
        1_1/lib/Duck/Dance/DanceWaltzBehavior.h
        1_1/lib/Duck/Dance/IDanceBehavior.h
        1_1/lib/Duck/Dance/NoDanceBehavior.h
        1_1/test/DuckTest.cpp
)

add_executable(${PROJECT_NAME}_2
        lib/Duck/Fly/FlyNoWay.h
        lib/Duck/Fly/FlyWithWings.h
        lib/Duck/Fly/IFlyBehavior.h
        lib/Duck/Quack/IQuackBehavior.h
        lib/Duck/Quack/MuteQuackBehavior.h
        lib/Duck/Quack/QuackBehavior.h
        lib/Duck/Quack/SqueakBehavior.h
        lib/Duck/DecoyDuck.h
        lib/Duck/Duck.h
        lib/Duck/MallardDuck.h
        lib/Duck/ModelDuck.h
        lib/Duck/RedheadDuck.h
        lib/Duck/RubberDuck.h
        lib/DuckFunctions.h
        SimUDuck.cpp
        lib/Duck/Dance/DanceMinuetBehavior.h
        lib/Duck/Dance/DanceWaltzBehavior.h
        lib/Duck/Dance/IDanceBehavior.h
        lib/Duck/Dance/NoDanceBehavior.h
)

add_executable(${PROJECT_NAME}Test_2
        lib/Duck/Fly/FlyNoWay.h
        lib/Duck/Fly/FlyWithWings.h
        lib/Duck/Fly/IFlyBehavior.h
        lib/Duck/Quack/IQuackBehavior.h
        lib/Duck/Quack/MuteQuackBehavior.h
        lib/Duck/Quack/QuackBehavior.h
        lib/Duck/Quack/SqueakBehavior.h
        lib/Duck/DecoyDuck.h
        lib/Duck/Duck.h
        lib/Duck/MallardDuck.h
        lib/Duck/ModelDuck.h
        lib/Duck/RedheadDuck.h
        lib/Duck/RubberDuck.h
        lib/DuckFunctions.h
        lib/Duck/Dance/DanceMinuetBehavior.h
        lib/Duck/Dance/DanceWaltzBehavior.h
        lib/Duck/Dance/IDanceBehavior.h
        lib/Duck/Dance/NoDanceBehavior.h
        test/DuckTest.cpp
)

target_link_libraries(${PROJECT_NAME}Test_1 gtest_main gmock)
target_link_libraries(${PROJECT_NAME}Test_2 gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test_1 COMMAND ${PROJECT_NAME}Test_1)
add_test(NAME ${PROJECT_NAME}Test_2 COMMAND ${PROJECT_NAME}Test_2)