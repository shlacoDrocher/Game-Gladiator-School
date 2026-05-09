//
// Created by Sigma on 06.05.2026.
//

#include "GladiatorFactory.h"

#include <vector>

static const std::vector<std::string> NAMES_LIST = {
    "Безымянный раб", "Суровый Галл", "Ловкий Фракиец",
    "Пленный варвар", "Хилый воришка", "Могучий германец"
};



std::unique_ptr<Gladiator> GladiatorFactory::CreateRandomGladiator(int level) {
    size_t index = rand() % NAMES_LIST.size();
    std::string name = NAMES_LIST[index];
    int randomHP = rand() % 50 + 51 + (level * 10);
    int ramdomDamage = rand() % 11 + 5 + (level * 2);
    int finalPrice = randomHP + (ramdomDamage * 2);
    return std::make_unique<Gladiator>(name, randomHP, ramdomDamage, finalPrice);
}