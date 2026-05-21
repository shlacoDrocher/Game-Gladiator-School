#include "Arena.h"
#include "../Factories/GladiatorFactory.h"
#include <iostream>
#include "Battle.h"

bool Arena::StartTournament(Gladiator* playerGladiator, int currentDay) {
    GladiatorFactory gladFactory;
    for (int wave = 1; wave <= 2; wave++) {
        auto enemy = gladFactory.CreateRandomGladiator(wave + currentDay);
        std::cout << "\n=== ВОЛНА " << wave << " === Ваш противник: " << enemy->GetName() << "!" << std::endl;

        Battle currentBattle(playerGladiator, enemy.get());
        bool survived = currentBattle.Start();

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
    std::cout << "\nГРАНД-ФИНАЛ НАЧИНАЕТСЯ!" << std::endl;

    Battle finalBattle(playerGladiator, boss);
    bool survived = finalBattle.Start();

    if (!survived) {
        std::cout << "\nВаш гладиатор пал на арене..." << std::endl;
        return false;
    }

    std::cout << "\nПоздравляем! Вы победили всех гладиаторов и доказали, что вы лучшая школа!" << std::endl;
    return true;
}