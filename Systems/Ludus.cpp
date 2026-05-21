#include "Ludus.h"
#include "../Core/GameManager.h"
#include <iostream>

bool Ludus::AddGladiator(std::unique_ptr<Gladiator> g) {
    if (gladiators.size() < MAX_GLADIATORS) {
        gladiators.push_back(std::move(g));
        return true;
    }
    return false;
}

void Ludus::ShowRoster() const {
    for (int i = 0; i < gladiators.size(); i++) {
        std::cout << i + 1 << ". " << gladiators[i]->GetName()
                  << " HP: " << gladiators[i]->GetHp() << "/" << gladiators[i]->GetMaxHp()
                  << " DMG: " << gladiators[i]->GetTotalDamage() << std::endl;
    }
}

void Ludus::NightHeal() const {
    for (auto & gladiator : gladiators) {
        gladiator->Heal(infirmary.GetHealAmount());
        gladiator->SetTrainedToday(false);
    }
}

bool Ludus::UpgradeDummy() {
    int cost = dummy.GetUpgradeCost();
    if (treasury.SpendFunds(cost)) {
        dummy.Upgrade();
        return true;
    }
    return false;
}

bool Ludus::UpgradeInfirmary() {
    int cost = infirmary.GetUpgradeCost();
    if (treasury.SpendFunds(cost)) {
        infirmary.Upgrade();
        return true;
    }
    return false;
}

TrainingResult Ludus::TrainGladiator(int index) {
    TrainingResult result = TrainingResult::INVALID_INDEX;

    if (index >= 0 && index < gladiators.size()) {
        auto& g = gladiators[index];
        if (!g->HasTrainedToday()) {
            g->AddBaseDamage(dummy.GetDamageBonus());
            g->AddBaseHp(dummy.GetHpBonus());
            g->SetTrainedToday(true);
            result = TrainingResult::SUCCESS;
        } else {
            result = TrainingResult::ALREADY_TRAINED;
        }
    }

    return result;
}

void Ludus::RemoveDeadGladiators() {
    for (int i = static_cast<int>(gladiators.size()) - 1; i >= 0; i--) {
        if (gladiators[i]->GetHp() <= 0) {
            std::cout << "Гладиатор " << gladiators[i]->GetName() << " мертв и вычеркнут из списков школы..." << std::endl;
            gladiators.erase(gladiators.begin() + i);
        }
    }
}

void Ludus::EquipItemMenu() {
    if (inventory.IsEmpty()) {
        std::cout << "Ваш склад пуст!" << std::endl;
        return;
    }

    std::cout << "\n ВАШ СКЛАД " << std::endl;
    inventory.ShowItems();

    std::cout << "Выберите предмет для использования (0 - отмена): ";
    int itemIdx = GameManager::GetValidInput(0, static_cast<int>(inventory.GetSize()));
    if (itemIdx == 0) return;

    std::cout << "Выберите бойца (от 1 до " << gladiators.size() << ") или 0 - отмена: ";
    int gladIdx = GameManager::GetValidInput(0, static_cast<int>(gladiators.size()));
    if (gladIdx == 0) return;

    Gladiator* g = gladiators[gladIdx - 1].get();
    std::unique_ptr<Item> item = inventory.TakeItem(itemIdx - 1);

    g->ReceiveItem(std::move(item));
}