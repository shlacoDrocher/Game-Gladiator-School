#include "Ludus.h"
#include "../Core/GameManager.h"
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
                  << " HP: " << gladiators[i]->GetHp() << "/" << gladiators[i]->GetMaxHp()
                  << " DMG: " << gladiators[i]->GetTotalDamage() << std::endl;
    }
}

void Ludus::NightHeal() const {
    for (auto & gladiator : gladiators) {
        gladiator -> Heal(infirmaryLevel *15);
        gladiator->SetTrainedToday(false);
    }
}

void Ludus::UpgradeDummy() {
    int cost = GetDummyUpgradeCost();
    if (gold >= cost) {
        gold -= cost;
        dummyLevel++;
        std::cout << "Манекен улучшен до уровня " << dummyLevel << "!" << std::endl;
    }
    else {
        std::cout << "Не хватает золота! Нужно: " << cost << std::endl;
    }
}

void Ludus::UpgradeInfirmary() {
    int cost = GetInfirmaryUpgradeCost();
    if (gold >= cost) {
        gold -= cost;
        infirmaryLevel++;
        std::cout << "Лазарет улучшен до уровня " << infirmaryLevel << "!" << std::endl;
    }
    else {
        std::cout << "Не хватает золота! Нужно: " << cost << std::endl;
    }
}

void Ludus::TrainGladiator(int index) const {
    if (index >=0 && index < gladiators.size()) {
        auto& g = gladiators[index];
        if (g -> HasTrainedToday() == false) {
            g -> AddBaseDamage(dummyLevel * 2);
            g->AddBaseHp(dummyLevel * 5);
            g->SetTrainedToday(true);
            std::cout << "Гладиатор был усилен! (Урон +" << (dummyLevel * 2)
                      << ", ХП +" << (dummyLevel * 5) << ")" << std::endl;
        } else {
            std::cout << "Этот боец слишком устал сегодня." << std::endl;
        }
    } else {
        std::cout << "Неверный номер гладиатора!" << std::endl;
    }
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

    if (dynamic_cast<Weapon*>(item.get())) {
        auto weapon = std::unique_ptr<Weapon>(dynamic_cast<Weapon*>(item.release()));
        g->EquipWeapon(std::move(weapon));
        std::cout << "Оружие экипировано!" << std::endl;
    }
    else if (dynamic_cast<Armor*>(item.get())) {
        auto armor = std::unique_ptr<Armor>(dynamic_cast<Armor*>(item.release()));
        g->EquipArmor(std::move(armor));
        std::cout << "Броня надета!" << std::endl;
    }

    else if (auto* potionPtr = dynamic_cast<Potion*>(item.get())) {
        g->Heal(potionPtr->GetHealAmount());
        std::cout << "Боец выпил зелье и восстановил здоровье!" << std::endl;
    }
}