//
// Created by Sigma on 05.05.2026.
//

#include "Ludus.h"

#include <iostream>

bool Ludus::AddGladiator(std::unique_ptr<Gladiator> g) {
    if (gladiators.size() < 5 ) {
        gladiators.push_back(std::move(g));
        return true;
    }
    return false;
}

void Ludus::ShowRoster() const {
    for (int i = 0; i < gladiators.size(); i++) {
        std::cout << i + 1 << ". " << gladiators[i]->GetName()
                  << " HP: " << gladiators[i]->GetMaxHp()
                  << " DMG: " << gladiators[i]->GetTotalDamage() << std::endl;
    }
}

void Ludus::NightHeal() {
    for (auto & gladiator : gladiators) {
        gladiator -> Heal(infirmaryLevel *10);
    }
}

void Ludus::UpgradeDummy() {
    if (gold >= 50) {
        gold -= 50;
        dummyLevel++;
        std::cout << "Манекен улучшено!" << std::endl;
    }
    else {
        std::cout << "Не хватает золота!" << std::endl;
    }
}

void Ludus::UpgradeInfirmary() {
    if (gold >= 50) {
        gold -= 50;
        infirmaryLevel++;
        std::cout << "Лазарет улучшен!" << std::endl;
    }
    else {
        std::cout << "Не хватает золота!" << std::endl;
    }
}

void Ludus::TrainGladiator(int index) {
    if (index >=0 && index < gladiators.size()) {
        auto& g = gladiators[index];
        if (g -> HasTrainedToday() == false) {
            g -> AddBaseDamage(dummyLevel * 2);
            g->SetTrainedToday(true);
            std::cout << "Гладиатор был усилен!" << std::endl;
        } else {
            std::cout << "Этот боец слишком устал сегодня." << std::endl;
        }
    } else {
        std::cout << "Неверный номер гладиатора!" << std::endl;
    }
}