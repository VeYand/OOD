cmake_minimum_required(VERSION 3.28)
project(lab2)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

add_executable(${PROJECT_NAME}_1-2
        1-2/WeatherStation/main.cpp
        1-2/WeatherStation/Observer/IObserver.h
        1-2/WeatherStation/Observable/IObservable.h
        1-2/WeatherStation/Observable/CObservable.h
        1-2/WeatherStation/Observer/CDisplay.h
        1-2/WeatherStation/Model/SWeatherInfo.h
        1-2/WeatherStation/Observer/CStatsDisplay.h
        1-2/WeatherStation/Observable/CWeatherData.h
        1-2/WeatherStation/Observer/CStatistics.h
)

add_executable(${PROJECT_NAME}_3
        3/WeatherStation/main.cpp
        3/WeatherStation/Observer/IObserver.h
        3/WeatherStation/Observable/IObservable.h
        3/WeatherStation/Observable/CObservable.h
        3/WeatherStation/Observer/CDisplay.h
        3/WeatherStation/Model/SWeatherInfo.h
        3/WeatherStation/Observer/CStatsDisplay.h
        3/WeatherStation/Observable/CWeatherData.h
        3/WeatherStation/Observer/CStatistics.h
)

add_executable(${PROJECT_NAME}_4
        4/WeatherStation/main.cpp
        4/WeatherStation/Observable/IObservable.h
        4/WeatherStation/Observable/CObservable.h
        4/WeatherStation/Observer/CDisplay.h
        4/WeatherStation/Model/SWeatherInfo.h
        4/WeatherStation/Observer/CStatsDisplay.h
        4/WeatherStation/Observable/CWeatherData.h
        4/WeatherStation/Observer/CStatistics.h
)

add_executable(${PROJECT_NAME}_5
        5-6/WeatherStation/main.cpp
        5-6/WeatherStation/Observable/IObservable.h
        5-6/WeatherStation/Observable/CObservable.h
        5-6/WeatherStation/Observer/CDisplay.h
        5-6/WeatherStation/Model/SWeatherInfo.h
        5-6/WeatherStation/Observer/CStatsDisplay.h
        5-6/WeatherStation/Observable/CWeatherData.h
        5-6/WeatherStation/Observer/CStatistics.h
        5-6/WeatherStation/Observer/CWindStatistics.h
        5-6/WeatherStation/Model/SWindInfo.h
)

add_executable(${PROJECT_NAME}_7
        7/main.cpp
        7/Observable/IObservable.h
        7/Observable/CObservable.h
        7/WeatherStation/Model/SWeatherInfo.h
        7/WeatherStation/CWeatherData.h
        7/WeatherStation/Model/SWindInfo.h
        7/Animal/Model/SAnimalInfo.h
        7/Animal/CAnimalData.h
        7/Animal/CCattishObserver.h
        7/Animal/CDoggyObserver.h
        7/Animal/CAnimalData.h
)

add_executable(${PROJECT_NAME}_8
        8/main.cpp
        8/Observable/IObservable.h
        8/Observable/CObservable.h
        8/WeatherStation/Model/SWeatherInfo.h
        8/WeatherStation/CWeatherData.h
        8/WeatherStation/Model/SWindInfo.h
)

add_executable(${PROJECT_NAME}Test_1-2
        1-2/WeatherStation/Observer/IObserver.h
        1-2/WeatherStation/Observable/IObservable.h
        1-2/WeatherStation/Observable/CObservable.h
        1-2/WeatherStation/Observer/CDisplay.h
        1-2/WeatherStation/Model/SWeatherInfo.h
        1-2/WeatherStation/Observer/CStatsDisplay.h
        1-2/WeatherStation/Observable/CWeatherData.h
        1-2/WeatherStation/Observer/CStatistics.h
        1-2/test/Test.cpp
)

add_executable(${PROJECT_NAME}Test_3
        3/WeatherStation/Observer/IObserver.h
        3/WeatherStation/Observable/IObservable.h
        3/WeatherStation/Observable/CObservable.h
        3/WeatherStation/Observer/CDisplay.h
        3/WeatherStation/Model/SWeatherInfo.h
        3/WeatherStation/Observer/CStatsDisplay.h
        3/WeatherStation/Observable/CWeatherData.h
        3/WeatherStation/Observer/CStatistics.h
        3/test/Test.cpp
)

add_executable(${PROJECT_NAME}Test_4
        4/WeatherStation/Observable/IObservable.h
        4/WeatherStation/Observable/CObservable.h
        4/WeatherStation/Observer/CDisplay.h
        4/WeatherStation/Model/SWeatherInfo.h
        4/WeatherStation/Observer/CStatsDisplay.h
        4/WeatherStation/Observable/CWeatherData.h
        4/WeatherStation/Observer/CStatistics.h
        4/test/CObservableTest.cpp
        4/test/DuoWeatherStationDisplayTest.cpp
        4/test/main.cpp
)

add_executable(${PROJECT_NAME}Test_5-6
        5-6/WeatherStation/Observable/IObservable.h
        5-6/WeatherStation/Observable/CObservable.h
        5-6/WeatherStation/Observer/CDisplay.h
        5-6/WeatherStation/Model/SWeatherInfo.h
        5-6/WeatherStation/Observer/CStatsDisplay.h
        5-6/WeatherStation/Observable/CWeatherData.h
        5-6/WeatherStation/Observer/CStatistics.h
        5-6/WeatherStation/Observer/CWindStatistics.h
        5-6/WeatherStation/Model/SWindInfo.h
        5-6/test/CObservableTest.cpp
        5-6/test/DuoWeatherStationDisplayTest.cpp
        5-6/test/main.cpp
)

target_link_libraries(${PROJECT_NAME}Test_1-2 gtest_main gmock)
target_link_libraries(${PROJECT_NAME}Test_3 gtest_main gmock)
target_link_libraries(${PROJECT_NAME}Test_4 gtest_main gmock)
target_link_libraries(${PROJECT_NAME}Test_5-6 gtest_main gmock)
enable_testing()
add_test(NAME ${PROJECT_NAME}Test_1-2 COMMAND ${PROJECT_NAME}Test_1-2)
add_test(NAME ${PROJECT_NAME}Test_3 COMMAND ${PROJECT_NAME}Test_3)
add_test(NAME ${PROJECT_NAME}Test_4 COMMAND ${PROJECT_NAME}Test_4)
add_test(NAME ${PROJECT_NAME}Test_5-6 COMMAND ${PROJECT_NAME}Test_5-6)
