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
        HydraulicPump.h
        ComponentMonitor.cpp
        ComponentMonitor.h
        Parser.cpp
        Parser.h
        CommandLineInterface.cpp
        CommandLineInterface.h)

if (MINGW)
    target_link_options(CMS PRIVATE -static)
endif()