cmake_minimum_required(VERSION 3.28)
project(lab4)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_1
        1/Designer/IDesigner.h
        1/ShapeFactory/IShapeFactory.h
        1/ShapeFactory/Shapes/Shape.h
        1/main.cpp
        1/Designer/PictureDraft.h
        1/Designer/Designer.h
        1/Canvas/ICanvas.h
        1/Canvas/PNGCanvas/stb_image_write.h
        1/Canvas/PNGCanvas/PNGCanvas.h
        1/Painter/IPainter.h
        1/Painter/Painter.h
        1/ShapeFactory/Shapes/Color.h
        1/ShapeFactory/Shapes/Ellipse.h
        1/ShapeFactory/Shapes/Point.h
        1/ShapeFactory/Shapes/Rectangle.h
        1/ShapeFactory/Shapes/RegularPolygon.h
        1/ShapeFactory/Shapes/Triangle.h
        1/ShapeFactory/ShapeFactory.h
        1/ShapeFactory/Shapes/Rect.h
        1/Client.h
        1/ShapeFactory/Shapes/ShapeType.h
        1/ShapeFactory/Shapes/Line.h
)
add_executable(${PROJECT_NAME}Test_1
        test/main.cpp
        test/1/Test.cpp
)

target_link_libraries(${PROJECT_NAME}Test_1 gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test_1 COMMAND ${PROJECT_NAME}Test_1)

