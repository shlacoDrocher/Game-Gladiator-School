//
// Created by Sigma on 05.05.2026.
//

#ifndef CODE_LUDUS_H
#define CODE_LUDUS_H
#include <memory>
#include "Inventory.h"
#include "../Entities/Gladiator.h"
#include <vector>


class Ludus {
    int gold = 150;
    int reputation = 0;
    int dummyLevel = 1;
    int infirmaryLevel = 1;
    std::vector<std::unique_ptr<Gladiator>> gladiators;
    Inventory inventory;
    public:
    Ludus() = default;
    [[nodiscard]] int getGold() const { return gold; }
    [[nodiscard]] int getReputation() const { return reputation; }
    void SpendGold(int amount) { gold -= amount;}
    void AddItemInventory(std::unique_ptr<Item> item) { inventory.AddItem(std::move(item)); }
    bool AddGladiator(std::unique_ptr<Gladiator> g);
    void ShowRoster() const;
    void TrainGladiator(int index);
    void UpgradeDummy();
    void UpgradeInfirmary();
    void NightHeal();
    void AddGold(int amount) { gold += amount; }
    int GetGladiatorCount() const { return static_cast<int>(gladiators.size()); }

    // Добавить репутацию за победу
    void AddReputation(int amount) { reputation += amount; }

    Gladiator* GetGladiator(int index) {
        if (index >= 0 && index < gladiators.size()) {
            return gladiators[index].get();
        }
        return nullptr;
    }
    void RemoveDeadGladiators();
    void EquipItemMenu();
};
#endif //CODE_LUDUS_H