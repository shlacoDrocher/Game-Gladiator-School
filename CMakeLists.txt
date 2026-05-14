cmake_minimum_required(VERSION 4.1)
project(code)

set(CMAKE_CXX_STANDARD 23)

add_executable(code Core/main.cpp
        Entities/Item.h
        Entities/Gladiator.h
        Entities/Gladiator.cpp
        Systems/Ludus.cpp
        Systems/Ludus.h
        Factories/ItemFactory.cpp
        Factories/ItemFactory.h
        Systems/Market.cpp
        Systems/Market.h
        Factories/GladiatorFactory.cpp
        Factories/GladiatorFactory.h
        Combat/CombatStrategies.cpp
        Combat/CombatStrategies.h
        Combat/Arena.cpp
        Combat/Arena.h
        Core/GameManager.cpp
        Core/GameManager.h
        Systems/Inventory.cpp
        Systems/Inventory.h
        Systems/Inventory.cpp
        Systems/Inventory.h)
