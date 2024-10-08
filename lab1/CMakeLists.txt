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
        1_2/lib/Duck/Fly/FlyNoWay.h
        1_2/lib/Duck/Fly/FlyWithWings.h
        1_2/lib/Duck/Fly/IFlyBehavior.h
        1_2/lib/Duck/Quack/IQuackBehavior.h
        1_2/lib/Duck/Quack/MuteQuackBehavior.h
        1_2/lib/Duck/Quack/QuackBehavior.h
        1_2/lib/Duck/Quack/SqueakBehavior.h
        1_2/lib/Duck/DecoyDuck.h
        1_2/lib/Duck/Duck.h
        1_2/lib/Duck/MallardDuck.h
        1_2/lib/Duck/ModelDuck.h
        1_2/lib/Duck/RedheadDuck.h
        1_2/lib/Duck/RubberDuck.h
        1_2/lib/DuckFunctions.h
        1_2/SimUDuck.cpp
        1_2/lib/Duck/Dance/DanceMinuetBehavior.h
        1_2/lib/Duck/Dance/DanceWaltzBehavior.h
        1_2/lib/Duck/Dance/IDanceBehavior.h
        1_2/lib/Duck/Dance/NoDanceBehavior.h
)

add_executable(${PROJECT_NAME}Test_2
        1_2/lib/Duck/Fly/FlyNoWay.h
        1_2/lib/Duck/Fly/FlyWithWings.h
        1_2/lib/Duck/Fly/IFlyBehavior.h
        1_2/lib/Duck/Quack/IQuackBehavior.h
        1_2/lib/Duck/Quack/MuteQuackBehavior.h
        1_2/lib/Duck/Quack/QuackBehavior.h
        1_2/lib/Duck/Quack/SqueakBehavior.h
        1_2/lib/Duck/DecoyDuck.h
        1_2/lib/Duck/Duck.h
        1_2/lib/Duck/MallardDuck.h
        1_2/lib/Duck/ModelDuck.h
        1_2/lib/Duck/RedheadDuck.h
        1_2/lib/Duck/RubberDuck.h
        1_2/lib/DuckFunctions.h
        1_2/lib/Duck/Dance/DanceMinuetBehavior.h
        1_2/lib/Duck/Dance/DanceWaltzBehavior.h
        1_2/lib/Duck/Dance/IDanceBehavior.h
        1_2/lib/Duck/Dance/NoDanceBehavior.h
        1_2/test/DuckTest.cpp
        1_2/test/MockDanceBehavior.h
        1_2/test/MockFlyBehavior.h
        1_2/test/MockQuackBehavior.h
)

add_executable(${PROJECT_NAME}_3
        1_3/lib/Duck/Fly/FlyBehavior.h
        1_3/lib/Duck/Duck.h
        1_3/SimUDuck.cpp
        1_3/lib/Duck/Quack/QuackBehavior.h
        1_3/lib/Duck/Dance/DanceBehavior.h
        1_3/lib/Duck/MallardDuck.h
        1_3/lib/Duck/DecoyDuck.h
        1_3/lib/Duck/ModelDuck.h
        1_3/lib/Duck/RedheadDuck.h
        1_3/lib/Duck/RubberDuck.h
        1_3/lib/DuckFunctions.h
)

add_executable(${PROJECT_NAME}_4
        1_4/main.cpp
        1_4/lib/shapes/Shape.h
        1_4/lib/shapes/Picture.h
        1_4/lib/shapes/strategy/IFigureStrategy.h
        1_4/lib/shapes/strategy/RectangleFigureStrategy.h
        1_4/lib/shapes/strategy/TextFigureStrategy.h
        1_4/lib/gfx/ICanvas.h
        1_4/lib/shapes/Point.h
        1_4/lib/shapes/Rect.h
        1_4/lib/shapes/exception/ShapeNotFoundException.h
        1_4/lib/gfx/PNGCanvas.h
        1_4/lib/shapes/strategy/TriangleFigureStrategy.h
        1_4/lib/shapes/strategy/LineFigureStrategy.h
        1_4/lib/shapes/strategy/CircleFigureStrategy.h
        1_4/lib/service/ShapeService.h
        1_4/lib/service/ShapeService.cpp
        1_4/lib/service/ShapeType.h
        1_4/lib/shapes/Color.h
        1_4/lib/shapes/Picture.cpp
        1_4/lib/shapes/exception/ShapeAlreadyExistsException.h
        1_4/lib/gfx/stb_image_write.h
        1_4/lib/gfx/stb_truetype.h
)

target_link_libraries(${PROJECT_NAME}_4)
target_link_libraries(${PROJECT_NAME}Test_1 gtest_main gmock)
target_link_libraries(${PROJECT_NAME}Test_2 gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test_1 COMMAND ${PROJECT_NAME}Test_1)
add_test(NAME ${PROJECT_NAME}Test_2 COMMAND ${PROJECT_NAME}Test_2)