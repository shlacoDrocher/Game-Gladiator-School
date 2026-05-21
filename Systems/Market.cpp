#include "Market.h"
#include "../Factories/ItemFactory.h"
#include "../Factories/GladiatorFactory.h"
#include <iostream>

void Market::UpdateAssortment(int currentDay) {
    GladiatorFactory gladFactory;
    dailyItems.clear();
    dailyGladiators.clear();

    WeaponFactory weaponFactory;
    ArmorFactory armorFactory;
    PotionFactory potionFactory;

    const ItemFactory* factories[] = { &weaponFactory, &armorFactory, &potionFactory };

    for (int index = 0; index < 3; index++) {
        int factoryChoice = rand() % 3;
        dailyItems.push_back(factories[factoryChoice]->CreateItem());
    }
    for (int i = 0; i < 2; i++) {
        dailyGladiators.push_back(gladFactory.CreateRandomGladiator(currentDay));
    }
}

void Market::ShowAssortment() const {
    std::cout << "\n ТОВАРЫ НА РЫНКЕ " << std::endl;
    for (size_t i = 0; i < dailyItems.size(); i++) {
        std::cout << "[Предмет " << i + 1 << "] " << dailyItems[i]->GetStats() << std::endl;
    }

    std::cout << "\n БОЙЦЫ НА ПРОДАЖУ " << std::endl;
    for (size_t i = 0; i < dailyGladiators.size(); i++) {
        std::cout << "[Боец " << i + 1 << "] "
                  << dailyGladiators[i]->GetName()
                  << " | ХП: " << dailyGladiators[i]->GetMaxHp()
                  << " | Урон: " << dailyGladiators[i]->GetTotalDamage()
                  << " | Цена: " << dailyGladiators[i]->GetPrice() << " монет" << std::endl;
    }
}

TransactionResult Market::BuyItem(int index, Ludus &school) {
    // По умолчанию ставим статус ошибки ввода
    TransactionResult result = TransactionResult::INVALID_INDEX;

    if (index >= 0 && index < dailyItems.size()) {
        int price = dailyItems[index]->GetPrice();

        if (school.SpendGold(price)) {
            school.AddItemInventory(std::move(dailyItems[index]));
            dailyItems.erase(dailyItems.begin() + index);
            result = TransactionResult::SUCCESS;
        } else {
            result = TransactionResult::INSUFFICIENT_FUNDS;
        }
    }

    return result;
}

TransactionResult Market::BuyGladiator(int index, Ludus &school) {
    TransactionResult result = TransactionResult::INVALID_INDEX;

    if (index >= 0 && index < dailyGladiators.size()) {
        int price = dailyGladiators[index]->GetPrice();

        if (school.getGold() >= price) {
            if (school.GetGladiatorCount() < Ludus::MAX_GLADIATORS) {
                school.SpendGold(price);
                school.AddGladiator(std::move(dailyGladiators[index]));
                dailyGladiators.erase(dailyGladiators.begin() + index);
                result = TransactionResult::SUCCESS;
            } else {
                result = TransactionResult::LUDUS_FULL;
            }
        } else {
            result = TransactionResult::INSUFFICIENT_FUNDS;
        }
    }

    return result;
}