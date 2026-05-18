#include "../Factories/GladiatorFactory.h"
#include <vector>

static const std::vector<std::string> NAMES_LIST = {
    "Безымянный раб", "Суровый Галл", "Ловкий Фракиец",
    "Пленный варвар", "Хилый воришка", "Могучий германец"
};

std::unique_ptr<Gladiator> GladiatorFactory::CreateRandomGladiator(int level) {
    size_t index = rand() % NAMES_LIST.size();
    std::string name = NAMES_LIST[index];
    int randomHP = rand() % 20 + 30 + (level * 2);
    int ramdomDamage = rand() % 4 + 3 + (level * 1);
    int finalPrice = randomHP + (ramdomDamage * 2);
    return std::make_unique<Gladiator>(name, randomHP, ramdomDamage, finalPrice);
}