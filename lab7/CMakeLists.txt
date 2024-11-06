cmake_minimum_required(VERSION 3.28)
project(lab7)

set(CMAKE_CXX_STANDARD 23)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}
        src/main.cpp
        src/CommonTypes.h
        src/Shape/CShape.h
        src/Shape/Style/CStyle.h
        src/Shape/CRectangle.h
        src/Shape/CEllipse.h
        src/Shape/CTriangle.h
        src/Canvas/ICanvas.h
        src/Slide/CSlide.h
        src/IDrawable.h
        src/Shape/Style/IStyle.h
        src/Shape/IShape.h
        src/Shape/IShapes.h
        src/Shape/IGroupShape.h
        src/Shape/GroupShape.h
        src/Slide/ISlide.h
        src/Canvas/Canvas.h
        src/ShapeFactory/ShapeFactory.h
        src/ShapeFactory/IShapeFactory.h
        src/ShapeFactory/ShapeType.h
        src/Menu/CMenu.h
)
add_executable(${PROJECT_NAME}Test_1
        test/main.cpp
        test/test.cpp
)

target_link_libraries(${PROJECT_NAME}Test_1 gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test_1 COMMAND ${PROJECT_NAME}Test_1)

