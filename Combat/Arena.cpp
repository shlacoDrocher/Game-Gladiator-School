#include "Arena.h"
#include "../Factories/GladiatorFactory.h"
#include "../Core/GameManager.h"
#include <iostream>

std::unique_ptr<ICombatStrategy> Arena::CreateStrategy(int choice) {
    if (choice == 1) return std::make_unique<AccurateAttack>();
    if (choice == 2) return std::make_unique<RecklessAttack>();
    return std::make_unique<DefensiveStance>();
}

bool Arena::ExecuteBattle(Gladiator* player, Gladiator* enemy) {
    while (player->GetHp() > 0 && enemy->GetHp() > 0) {
        player->SetBlocking(false);
        player->SetVulnerable(false);

        std::cout << "\n[ВЫ] ХП: " << player->GetHp() << " |[ВРАГ] ХП: " << enemy->GetHp() << std::endl;
        std::cout << "Выберите действие:\n1. Точная атака\n2. Безрассудный удар\n3. Глухая защита" << std::endl;

        int choice = GameManager::GetValidInput(1, 3);
        auto activeStrategy = CreateStrategy(choice);
        activeStrategy->Execute(player, enemy);

        if (enemy->GetHp() <= 0) {
            std::cout << "\nВраг повержен!" << std::endl;
            break;
        }

        enemy->SetBlocking(false);
        enemy->SetVulnerable(false);

        int aiRoll = rand() % 100;
        int enemyChoice = (aiRoll < 50) ? 1 : ((aiRoll < 80) ? 2 : 3);

        auto enemyStrategy = CreateStrategy(enemyChoice);

        std::cout << "\n--- Ход противника ---" << std::endl;
        enemyStrategy->Execute(enemy, player);
    }

    return player->GetHp() > 0;
}

bool Arena::StartTournament(Gladiator* playerGladiator, int currentDay) {
    GladiatorFactory gladFactory;
    for (int wave = 1; wave <= 2; wave++) {
        auto enemy = gladFactory.CreateRandomGladiator(wave + currentDay);
        std::cout << "\n=== ВОЛНА " << wave << " === Ваш противник: " << enemy->GetName() << "!" << std::endl;

        bool survived = ExecuteBattle(playerGladiator, enemy.get());

        if (!survived) {
            std::cout << "\nВаш гладиатор пал на арене..." << std::endl;
            return false;
        }

        if (wave < 2) {
            int waveHeal = playerGladiator->GetMaxHp() / 2;
            playerGladiator->Heal(waveHeal);
            std::cout << "[ПЕРЕРЫВ] Ваш боец отдыхает и восстанавливает " << waveHeal << " ХП!" << std::endl;
        }
    }

    std::cout << "\nТурнир пройден! Гладиатор возвращается героем!" << std::endl;
    return true;
}

bool Arena::FightBoss(Gladiator *playerGladiator, Gladiator* boss) {
    std::cout << "\nБИТВА НАЧИНАЕТСЯ!" << std::endl;

    bool survived = ExecuteBattle(playerGladiator, boss);

    if (!survived) {
        std::cout << "\nВаш гладиатор пал на арене..." << std::endl;
        return false;
    }

    std::cout << "\nПоздравляем! Вы победили всех гладиаторов и доказали, что вы лучшая школа!" << std::endl;
    return true;
}