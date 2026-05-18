#include "../Factories//ItemFactory.h"
#include <vector>

struct WeaponPreset {
    std::string name;
    int price;
    int damage;
};

struct ArmorPreset {
    std::string name;
    int price;
    int hp;
};

struct HealthPreset {
    std::string name;
    int price;
    int heal;
};

static const std::vector<WeaponPreset> WEAPON_LIST = {
    {"Ржавый кинжал", 15, 5},
    {"Гладиус", 50, 15},
    {"Стальной двуручник", 120, 30},
    {"Топор варвара", 150, 35},
    {"Копьё", 25, 23}
};

static const std::vector<ArmorPreset> ARMOR_LIST = {
    {"Кожаная куртка", 30, 20},
    {"Кольчуга", 80, 40},
    {"Броня легионера", 150, 60}
};

static const std::vector<HealthPreset> HEALTH_LIST = {
    {"Слабое зелье", 10, 20},
    {"Обычное зелье", 25, 50},
    {"Великое зелье", 60, 100}
};

std::unique_ptr<Item> WeaponFactory::CreateItem() const {
    size_t index = rand() % WEAPON_LIST.size();
    const auto& preset = WEAPON_LIST[index];
    return std::make_unique<Weapon>(preset.name, preset.price, preset.damage);
}

std::unique_ptr<Item> ArmorFactory::CreateItem() const {
    size_t index = rand() % ARMOR_LIST.size();
    const auto& preset = ARMOR_LIST[index];
    return std::make_unique<Armor>(preset.name, preset.price, preset.hp);
}

std::unique_ptr<Item> PotionFactory::CreateItem() const {
    size_t index = rand() % HEALTH_LIST.size();
    const auto& preset = HEALTH_LIST[index];
    return std::make_unique<Potion>(preset.name, preset.price, preset.heal);
}