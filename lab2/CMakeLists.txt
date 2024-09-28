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
        WeatherStation/main.cpp
        WeatherStation/Observer/IObserver.h
        WeatherStation/Observable/IObservable.h
        WeatherStation/Observable/CObservable.h
        WeatherStation/Observer/CDisplay.h
        WeatherStation/Model/SWeatherInfo.h
        WeatherStation/Observer/CStatsDisplay.h
        WeatherStation/Observable/CWeatherData.h
        WeatherStation/Observer/CStatistics.h
)

add_executable(${PROJECT_NAME}Test_1
        WeatherStation/Observer/IObserver.h
        WeatherStation/Observable/IObservable.h
        WeatherStation/Observable/CObservable.h
        WeatherStation/Observer/CDisplay.h
        WeatherStation/Model/SWeatherInfo.h
        WeatherStation/Observer/CStatsDisplay.h
        WeatherStation/Observable/CWeatherData.h
        WeatherStation/Observer/CStatistics.h
        test/Test.cpp
)

target_link_libraries(${PROJECT_NAME}Test_1 gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test_1 COMMAND ${PROJECT_NAME}Test_1)