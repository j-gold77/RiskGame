cmake_minimum_required(VERSION 3.17)
project(RiskGame)

set(CMAKE_CXX_STANDARD 14)

add_executable(RiskGame main.cpp Cards.h Cards.cpp Player.h Player.cpp Map.h Map.cpp Orders.cpp Orders.h GameEngine.cpp
        GameEngine.h LogObserver.cpp LogObserver.h CommandProcessing.cpp CommandProcessing.h PlayerStretegy.h
        PlayerStrategy.cpp)