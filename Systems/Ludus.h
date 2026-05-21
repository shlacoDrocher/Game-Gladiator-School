#ifndef CODE_LUDUS_H
#define CODE_LUDUS_H
#include <memory>
#include "Inventory.h"
#include "../Entities/Gladiator.h"
#include <vector>
#include "Buildings.h"

class Ludus {
    int gold = 200;
    int reputation = 0;
    TrainingDummy dummy;
    Infirmary infirmary;
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
    void NightHeal() const;
    void AddGold(int amount) { gold += amount; }
    [[nodiscard]] int GetGladiatorCount() const { return static_cast<int>(gladiators.size()); }

    void AddReputation(int amount) { reputation += amount; }

    [[nodiscard]] Gladiator* GetGladiator(int index) const {
        if (index >= 0 && index < gladiators.size()) {
            return gladiators[index].get();
        }
        return nullptr;
    }
    void RemoveDeadGladiators();
    void EquipItemMenu();
    [[nodiscard]] int GetDummyUpgradeCost() const { return dummy.GetUpgradeCost(); }
    [[nodiscard]] int GetInfirmaryUpgradeCost() const { return infirmary.GetUpgradeCost(); }
};

#endif //CODE_LUDUS_H