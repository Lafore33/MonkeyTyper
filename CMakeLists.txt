cmake_minimum_required(VERSION 3.27)
project(MonkeyTyper)

set(CMAKE_CXX_STANDARD 20)

include_directories(/usr/local/lib/cmake/SFML)

find_package(SFML 2.6.1 COMPONENTS system window graphics REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})

add_executable(MonkeyTyper
        GameSettings.cpp
        GameSettings.h
        Menu.h
        Menu.cpp
        main.cpp
        Settings.cpp
        Settings.h
        Button.h
        LeaderBoard.cpp
        LeaderBoard.h
        GameSession.cpp
        GameSession.h
        PreGame.cpp
        PreGame.h
        SavedGame.cpp
        SavedGame.h
        AfterGame.cpp
        AfterGame.h
        Game.cpp
        Game.h)
target_link_libraries(MonkeyTyper sfml-system sfml-window sfml-graphics sfml-audio)
