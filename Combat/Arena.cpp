#include "Arena.h"
#include "../Factories/GladiatorFactory.h"
#include "../Core/GameManager.h"
#include <iostream>

bool Arena::StartTournament(Gladiator* playerGladiator, int currentDay) {
    for (int wave = 1; wave <= 2; wave++) {
        auto enemy = GladiatorFactory::CreateRandomGladiator(wave + currentDay);
        std::cout << "\n ВОЛНА " << wave << " Ваш противник: " << enemy->GetName() << "!" << std::endl;

        while (playerGladiator->GetHp() > 0 && enemy->GetHp() > 0) {
            playerGladiator->SetBlocking(false);
            playerGladiator->SetVulnerable(false);

            std::cout << "\n[ВЫ] ХП: " << playerGladiator->GetHp() << " |[ВРАГ] ХП: " << enemy->GetHp() << std::endl;
            std::cout << "Выберите действие:\n1. Точная атака\n2. Безрассудный удар\n3. Глухая защита" << std::endl;

            int choice = GameManager::GetValidInput(1,3);

            std::unique_ptr<ICombatStrategy> activeStrategy;
            if (choice == 1) activeStrategy = std::make_unique<AccurateAttack>();
            else if (choice == 2) activeStrategy = std::make_unique<RecklessAttack>();
            else activeStrategy = std::make_unique<DefensiveStance>();

            activeStrategy->Execute(playerGladiator, enemy.get());

            if (enemy->GetHp() <= 0) {
                std::cout << "\nВраг повержен!" << std::endl;

                if (wave < 2) {
                    int waveHeal = playerGladiator->GetMaxHp() / 2;
                    playerGladiator->Heal(waveHeal);
                    std::cout << "[ПЕРЕРЫВ] Ваш боец отдыхает и восстанавливает " << waveHeal << " ХП перед следующим боем!" << std::endl;
                }
                break;
            }

            enemy->SetBlocking(false);
            enemy->SetVulnerable(false);

            int aiRoll = rand() % 100;
            int enemyChoice;
            if (aiRoll < 50) enemyChoice = 1;
            else if (aiRoll < 80) enemyChoice = 2;
            else enemyChoice = 3;

            std::unique_ptr<ICombatStrategy> enemyStrategy;
            if (enemyChoice == 1) enemyStrategy = std::make_unique<AccurateAttack>();
            else if (enemyChoice == 2) enemyStrategy = std::make_unique<RecklessAttack>();
            else enemyStrategy = std::make_unique<DefensiveStance>();

            std::cout << "\n Ход противника " << std::endl;
            enemyStrategy->Execute(enemy.get(), playerGladiator);
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

            int choice = GameManager::GetValidInput(1,3);

            std::unique_ptr<ICombatStrategy> activeStrategy;
            if (choice == 1) activeStrategy = std::make_unique<AccurateAttack>();
            else if (choice == 2) activeStrategy = std::make_unique<RecklessAttack>();
            else activeStrategy = std::make_unique<DefensiveStance>();

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

            std::unique_ptr<ICombatStrategy> enemyStrategy;
            if (enemyChoice == 1) enemyStrategy = std::make_unique<AccurateAttack>();
            else if (enemyChoice == 2) enemyStrategy = std::make_unique<RecklessAttack>();
            else enemyStrategy = std::make_unique<DefensiveStance>();

            std::cout << "\n Ход противника " << std::endl;
            enemyStrategy->Execute(boss, playerGladiator);
        }

        if (playerGladiator->GetHp() <= 0) {
            std::cout << "\nВаш гладиатор пал на арене..." << std::endl;
            return false;
        }

    std::cout << "\nТурнир пройден! Гладиатор возвращается героем!" << std::endl;
    std::cout << "\nПоздравляю вы победили всех гладиаторов и доказали что вы самая лучшая школа!" << std::endl;
    return true;
}