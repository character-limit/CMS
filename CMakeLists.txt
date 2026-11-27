cmake_minimum_required(VERSION 4.2)
project(CMS)

set(CMAKE_CXX_STANDARD 20)

add_executable(CMS main.cpp
        Component.cpp
        Component.h
        Format.cpp
        Format.h
        Status.cpp
        Status.h
        EngineComponent.cpp
        EngineComponent.h
        LandingGearComponent.cpp
        LandingGearComponent.h
        HydraulicPump.cpp
        HydraulicPump.h)
