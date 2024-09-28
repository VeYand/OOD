cmake_minimum_required(VERSION 3.28)
project(lab1)

set(CMAKE_CXX_STANDARD 20)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

add_executable(${PROJECT_NAME}_1
        WeatherStation/main.cpp
        WeatherStation/Observer/IObserver.h
        WeatherStation/Observarble/IObservable.h
        WeatherStation/Observarble/CObservable.h
        WeatherStation/Observer/CDisplay.h
        WeatherStation/Model/SWeatherInfo.h
        WeatherStation/Observer/CStatsDisplay.h
        WeatherStation/Observarble/CWeatherData.h
)
