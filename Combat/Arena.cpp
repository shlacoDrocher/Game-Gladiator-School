//
// Created by Sigma on 09.05.2026.
//

#include "Arena.h"
#include "../Factories/GladiatorFactory.h"
#include <iostream>

// ДОБАВИЛИ Arena::
bool Arena::StartTournament(Gladiator* playerGladiator, int currentDay) {
    for (int wave = 1; wave <= 2; wave++) {
        auto enemy = GladiatorFactory::CreateRandomGladiator(wave + currentDay);
        std::cout << "\n ВОЛНА " << wave << " Ваш противник: " << enemy->GetName() << "!" << std::endl;

        while (playerGladiator->GetHp() > 0 && enemy->GetHp() > 0) {
            playerGladiator->SetBlocking(false);
            playerGladiator->SetVulnerable(false);

            std::cout << "\n[ВЫ] ХП: " << playerGladiator->GetHp() << " |[ВРАГ] ХП: " << enemy->GetHp() << std::endl;
            std::cout << "Выберите действие:\n1. Точная атака\n2. Безрассудный удар\n3. Глухая защита" << std::endl;

            int choice;
            std::cin >> choice;

            ICombatStrategy* activeStrategy = nullptr;
            if (choice == 1) activeStrategy = &strategyAccurate;
            else if (choice == 2) activeStrategy = &strategyReckless;
            else activeStrategy = &strategyDefensive;

            activeStrategy->Execute(playerGladiator, enemy.get());

            if (enemy->GetHp() <= 0) {
                std::cout << "Враг повержен!" << std::endl;
                break;
            }

            enemy->SetBlocking(false);
            enemy->SetVulnerable(false);

            int aiRoll = rand() % 100;
            int enemyChoice;
            if (aiRoll < 50) enemyChoice = 1;
            else if (aiRoll < 80) enemyChoice = 2;
            else enemyChoice = 3;

            if (enemyChoice == 1) activeStrategy = &strategyAccurate;
            else if (enemyChoice == 2) activeStrategy = &strategyReckless;
            else activeStrategy = &strategyDefensive;

            std::cout << "\n Ход противника " << std::endl;
            activeStrategy->Execute(enemy.get(), playerGladiator);
        }

        if (playerGladiator->GetHp() <= 0) {
            std::cout << "\nВаш гладиатор пал на арене..." << std::endl;
            return false;
        }
    }

    std::cout << "\nТурнир пройден! Гладиатор возвращается героем!" << std::endl;
    return true;
}

bool Arena::FightBoss(Gladiator *playerGladiator, Gladiator* boss) {

        while (playerGladiator->GetHp() > 0 && boss->GetHp() > 0) {
            playerGladiator->SetBlocking(false);
            playerGladiator->SetVulnerable(false);

            std::cout << "\n[ВЫ] ХП: " << playerGladiator->GetHp() << " |[ВРАГ] ХП: " << boss->GetHp() << std::endl;
            std::cout << "Выберите действие:\n1. Точная атака\n2. Безрассудный удар\n3. Глухая защита" << std::endl;

            int choice;
            std::cin >> choice;

            ICombatStrategy* activeStrategy = nullptr;
            if (choice == 1) activeStrategy = &strategyAccurate;
            else if (choice == 2) activeStrategy = &strategyReckless;
            else activeStrategy = &strategyDefensive;

            activeStrategy->Execute(playerGladiator, boss);

            if (boss->GetHp() <= 0) {
                std::cout << "Враг повержен!" << std::endl;
                break;
            }

            boss->SetBlocking(false);
            boss->SetVulnerable(false);

            int aiRoll = rand() % 100;
            int enemyChoice;
            if (aiRoll < 50) enemyChoice = 1;
            else if (aiRoll < 80) enemyChoice = 2;
            else enemyChoice = 3;

            if (enemyChoice == 1) activeStrategy = &strategyAccurate;
            else if (enemyChoice == 2) activeStrategy = &strategyReckless;
            else activeStrategy = &strategyDefensive;

            std::cout << "\n Ход противника " << std::endl;
            activeStrategy->Execute(boss, playerGladiator);
        }

        if (playerGladiator->GetHp() <= 0) {
            std::cout << "\nВаш гладиатор пал на арене..." << std::endl;
            return false;
        }

    std::cout << "\nТурнир пройден! Гладиатор возвращается героем!" << std::endl;
    std::cout << "\nПоздравляю вы победили всех гладиаторов и доказали что вы самая лучшая школа!" << std::endl;
    return true;
}