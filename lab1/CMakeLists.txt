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

add_executable(${PROJECT_NAME}
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

add_executable(${PROJECT_NAME}Test
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

target_link_libraries(${PROJECT_NAME}Test gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test COMMAND ${PROJECT_NAME}Test)