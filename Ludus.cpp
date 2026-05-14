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
                  << " HP: " << gladiators[i]->GetHp() << "/" << gladiators[i]->GetMaxHp()
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
    int itemIdx; std::cin >> itemIdx;
    if (itemIdx <= 0 || itemIdx > inventory.GetSize()) return;

    std::cout << "Выберите бойца (от 1 до " << gladiators.size() << "): ";
    int gladIdx; std::cin >> gladIdx;
    if (gladIdx <= 0 || gladIdx > gladiators.size()) return;

    Gladiator* g = gladiators[gladIdx - 1].get();
    std::unique_ptr<Item> item = inventory.TakeItem(itemIdx - 1);

    if (auto weapon = dynamic_cast<Weapon*>(item.get())) {
        g->EquipWeapon(std::unique_ptr<Weapon>(static_cast<Weapon*>(item.release())));
        std::cout << "Оружие экипировано!" << std::endl;
    }
    else if (auto armor = dynamic_cast<Armor*>(item.get())) {
        g->EquipArmor(std::unique_ptr<Armor>(static_cast<Armor*>(item.release())));
        std::cout << "Броня надета!" << std::endl;
    }
    else if (auto potion = dynamic_cast<Potion*>(item.get())) {
        g->Heal(potion->GetHealAmount());
        std::cout << "Боец выпил зелье и восстановил здоровье!" << std::endl;
    }
}