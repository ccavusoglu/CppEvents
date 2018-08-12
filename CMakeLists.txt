cmake_minimum_required(VERSION 3.10)
project(CppEvents)

set(CMAKE_CXX_STANDARD 17)

add_executable(CppEvents
        main.cpp EventManager.cpp EventManager.h
        EventCallback.h EventType.h
        IEventBase.h GetUserEvent.h GetUserSettingsEvent.h Utility.h)