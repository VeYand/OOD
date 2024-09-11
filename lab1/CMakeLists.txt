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
        lab1_1/lib/Duck/Fly/FlyNoWay.h
        lab1_1/lib/Duck/Fly/FlyWithWings.h
        lab1_1/lib/Duck/Fly/IFlyBehavior.h
        lab1_1/lib/Duck/Quack/IQuackBehavior.h
        lab1_1/lib/Duck/Quack/MuteQuackBehavior.h
        lab1_1/lib/Duck/Quack/QuackBehavior.h
        lab1_1/lib/Duck/Quack/SqueakBehavior.h
        lab1_1/lib/Duck/DecoyDuck.h
        lab1_1/lib/Duck/Duck.h
        lab1_1/lib/Duck/MallardDuck.h
        lab1_1/lib/Duck/ModelDuck.h
        lab1_1/lib/Duck/RedheadDuck.h
        lab1_1/lib/Duck/RubberDuck.h
        lab1_1/lib/DuckFunctions.h
        lab1_1/SimUDuck.cpp
        lab1_1/lib/Duck/Dance/DanceMinuetBehavior.h
        lab1_1/lib/Duck/Dance/DanceWaltzBehavior.h
        lab1_1/lib/Duck/Dance/IDanceBehavior.h
        lab1_1/lib/Duck/Dance/NoDanceBehavior.h
)

add_executable(${PROJECT_NAME}Test_1
        lab1_1/lib/Duck/Fly/FlyNoWay.h
        lab1_1/lib/Duck/Fly/FlyWithWings.h
        lab1_1/lib/Duck/Fly/IFlyBehavior.h
        lab1_1/lib/Duck/Quack/IQuackBehavior.h
        lab1_1/lib/Duck/Quack/MuteQuackBehavior.h
        lab1_1/lib/Duck/Quack/QuackBehavior.h
        lab1_1/lib/Duck/Quack/SqueakBehavior.h
        lab1_1/lib/Duck/DecoyDuck.h
        lab1_1/lib/Duck/Duck.h
        lab1_1/lib/Duck/MallardDuck.h
        lab1_1/lib/Duck/ModelDuck.h
        lab1_1/lib/Duck/RedheadDuck.h
        lab1_1/lib/Duck/RubberDuck.h
        lab1_1/lib/DuckFunctions.h
        lab1_1/lib/Duck/Dance/DanceMinuetBehavior.h
        lab1_1/lib/Duck/Dance/DanceWaltzBehavior.h
        lab1_1/lib/Duck/Dance/IDanceBehavior.h
        lab1_1/lib/Duck/Dance/NoDanceBehavior.h
        lab1_1/test/DuckTest.cpp
)

add_executable(${PROJECT_NAME}_2
        lab1_2/lib/Duck/Fly/FlyNoWay.h
        lab1_2/lib/Duck/Fly/FlyWithWings.h
        lab1_2/lib/Duck/Fly/IFlyBehavior.h
        lab1_2/lib/Duck/Quack/IQuackBehavior.h
        lab1_2/lib/Duck/Quack/MuteQuackBehavior.h
        lab1_2/lib/Duck/Quack/QuackBehavior.h
        lab1_2/lib/Duck/Quack/SqueakBehavior.h
        lab1_2/lib/Duck/DecoyDuck.h
        lab1_2/lib/Duck/Duck.h
        lab1_2/lib/Duck/MallardDuck.h
        lab1_2/lib/Duck/ModelDuck.h
        lab1_2/lib/Duck/RedheadDuck.h
        lab1_2/lib/Duck/RubberDuck.h
        lab1_2/lib/DuckFunctions.h
        lab1_2/SimUDuck.cpp
        lab1_2/lib/Duck/Dance/DanceMinuetBehavior.h
        lab1_2/lib/Duck/Dance/DanceWaltzBehavior.h
        lab1_2/lib/Duck/Dance/IDanceBehavior.h
        lab1_2/lib/Duck/Dance/NoDanceBehavior.h
)

add_executable(${PROJECT_NAME}Test_2
        lab1_2/lib/Duck/Fly/FlyNoWay.h
        lab1_2/lib/Duck/Fly/FlyWithWings.h
        lab1_2/lib/Duck/Fly/IFlyBehavior.h
        lab1_2/lib/Duck/Quack/IQuackBehavior.h
        lab1_2/lib/Duck/Quack/MuteQuackBehavior.h
        lab1_2/lib/Duck/Quack/QuackBehavior.h
        lab1_2/lib/Duck/Quack/SqueakBehavior.h
        lab1_2/lib/Duck/DecoyDuck.h
        lab1_2/lib/Duck/Duck.h
        lab1_2/lib/Duck/MallardDuck.h
        lab1_2/lib/Duck/ModelDuck.h
        lab1_2/lib/Duck/RedheadDuck.h
        lab1_2/lib/Duck/RubberDuck.h
        lab1_2/lib/DuckFunctions.h
        lab1_2/lib/Duck/Dance/DanceMinuetBehavior.h
        lab1_2/lib/Duck/Dance/DanceWaltzBehavior.h
        lab1_2/lib/Duck/Dance/IDanceBehavior.h
        lab1_2/lib/Duck/Dance/NoDanceBehavior.h
        lab1_2/test/DuckTest.cpp
)

target_link_libraries(${PROJECT_NAME}Test_1 gtest_main)
target_link_libraries(${PROJECT_NAME}Test_2 gtest_main)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test_1 COMMAND ${PROJECT_NAME}Test_1)
add_test(NAME ${PROJECT_NAME}Test_2 COMMAND ${PROJECT_NAME}Test_2)

