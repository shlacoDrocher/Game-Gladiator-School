cmake_minimum_required(VERSION 4.1)
project(code)

set(CMAKE_CXX_STANDARD 23)

add_executable(code main.cpp
        Item.h
        Gladiator.h
        Gladiator.cpp
        Ludus.cpp
        Ludus.h
        ItemFactory.cpp
        ItemFactory.h
        Market.cpp
        Market.h
        GladiatorFactory.cpp
        GladiatorFactory.h)
