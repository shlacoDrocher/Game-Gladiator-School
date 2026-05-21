#ifndef CODE_LUDUS_H
#define CODE_LUDUS_H
#include <memory>
#include "Inventory.h"
#include "../Entities/Gladiator.h"
#include <vector>
#include "Buildings.h"
#include "Treasury.h"

enum class TrainingResult {
    SUCCESS,
    ALREADY_TRAINED,
    INVALID_INDEX
};

class Ludus {
public:
    static const int MAX_GLADIATORS = 5;
private:
    Treasury treasury;
    int reputation = 0;
    TrainingDummy dummy;
    Infirmary infirmary;
    std::vector<std::unique_ptr<Gladiator>> gladiators;
    Inventory inventory;
public:
    Ludus() = default;

    [[nodiscard]] int getGold() const { return treasury.GetBalance(); }
    [[nodiscard]] int getReputation() const { return reputation; }

    // Обертки для работы с деньгами
    bool SpendGold(int amount) { return treasury.SpendFunds(amount); }
    void AddGold(int amount) { treasury.AddFunds(amount); }

    void AddItemInventory(std::unique_ptr<Item> item) { inventory.AddItem(std::move(item)); }
    bool AddGladiator(std::unique_ptr<Gladiator> g);
    void ShowRoster() const;

    TrainingResult TrainGladiator(int index);
    bool UpgradeDummy();
    bool UpgradeInfirmary();

    void NightHeal() const;
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