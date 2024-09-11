cmake_minimum_required(VERSION 3.28)
project(lab1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1
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
