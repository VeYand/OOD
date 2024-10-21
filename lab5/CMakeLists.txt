cmake_minimum_required(VERSION 3.28)
project(lab5)

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
        src/Document/IDocument.h
        src/Document/Paragraph/IParagraph.h
        src/Document/Image/IImage.h
        src/Document/CConstDocumentItem.h
        src/Document/CDocumentItem.h
        src/Menu/CMenu.h
        src/Document/Command/ICommand.h
        src/Document/Command/AbstractCommand.h
        src/Document/CDocument.h
        src/Document/Image/СImage.h
        src/Document/Path.h
        src/Document/Paragraph/CParagraph.h
        src/Document/History/History.h
        src/Document/Command/InsertParagraphCommand.h
        src/Document/Command/InsertImageCommand.h
        src/Document/Command/DeleteItemCommand.h
        src/Document/Command/SetTitleCommand.h
        src/Document/Command/ReplaceTextCommand.h
        src/Document/Html/HtmlUtils.h
        src/Document/Command/ResizeImageCommand.h
        src/Document/Utils/FileUtils.h
)
add_executable(${PROJECT_NAME}Test_1
        test/main.cpp
        test/Test.cpp
)

target_link_libraries(${PROJECT_NAME}Test_1 gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test_1 COMMAND ${PROJECT_NAME}Test_1)

