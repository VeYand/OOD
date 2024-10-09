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
        test/main.cpp
        test/1_2/Test.cpp
)

add_executable(${PROJECT_NAME}_3
        3/OutputStream/IOutputDataStream.h
        3/OutputStream/CFileOutputStream.h
        3/main.cpp
        3/InputStream/IInputDataStream.h
        3/InputStream/CFileInputStream.h
        3/InputStream/CMemoryInputStream.h
        3/OutputStream/CMemoryOutputStream.h
        3/InputStream/Decorator/CInputStreamDecorator.h
        3/InputStream/Decorator/CDecompressInputStream.h
        3/OutputStream/Decorator/COutputStreamDecorator.h
        3/OutputStream/Decorator/CCompressOutputStream.h
        3/OutputStream/Decorator/CEncryptOutputStream.h
        3/InputStream/Decorator/CDecryptInputStream.h
)

target_link_libraries(${PROJECT_NAME}Test_1-2 gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test_1-2 COMMAND ${PROJECT_NAME}Test_1-2)

