#include "Battle.h"
#include "../Core/GameManager.h"
#include <iostream>

Battle::Battle(Gladiator* p, Gladiator* e) : player(p), enemy(e), roundCount(1) {}

std::unique_ptr<ICombatStrategy> Battle::CreateStrategy(int choice) {
    if (choice == 1) return std::make_unique<AccurateAttack>();
    if (choice == 2) return std::make_unique<RecklessAttack>();
    return std::make_unique<DefensiveStance>();
}

bool Battle::Start() {
    std::cout << "\nБОЙ НАЧИНАЕТСЯ! " << player->GetName() << " против " << enemy->GetName() << std::endl;

    while (player->GetHp() > 0 && enemy->GetHp() > 0) {
        std::cout << "\n=== РАУНД " << roundCount << " ===" << std::endl;

        player->SetBlocking(false);
        player->SetVulnerable(false);

        std::cout << "[ВЫ] ХП: " << player->GetHp() << " | [ВРАГ] ХП: " << enemy->GetHp() << std::endl;
        std::cout << "Выберите действие:\n1. Точная атака\n2. Безрассудный удар\n3. Глухая защита" << std::endl;

        int choice = GameManager::GetValidInput(1, 3);
        auto activeStrategy = CreateStrategy(choice);
        activeStrategy->Execute(player, enemy);

        if (enemy->GetHp() <= 0) {
            std::cout << "\nВраг повержен в " << roundCount << " раунде!" << std::endl;
            break;
        }

        enemy->SetBlocking(false);
        enemy->SetVulnerable(false);

        int aiRoll = rand() % 100;
        int enemyChoice = (aiRoll < 50) ? 1 : ((aiRoll < 80) ? 2 : 3);

        auto enemyStrategy = CreateStrategy(enemyChoice);

        std::cout << "\n--- Ход противника ---" << std::endl;
        enemyStrategy->Execute(enemy, player);

        roundCount++; // Увеличиваем раунд
    }

    return player->GetHp() > 0;
}