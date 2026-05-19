#include "Market.h"
#include "../Factories/ItemFactory.h"
#include "../Factories/GladiatorFactory.h"
#include <iostream>

void Market::UpdateAssortment(int currentDay) {
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
        dailyGladiators.push_back(GladiatorFactory::CreateRandomGladiator(currentDay));
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

void Market::BuyItem(int index, Ludus &school) {
    if (index >= 0 && index < dailyItems.size()) {
        int price = dailyItems[index]->GetPrice();

        if (school.getGold() >= price) {
            school.SpendGold(price);
            school.AddItemInventory(std::move(dailyItems[index]));
            dailyItems.erase(dailyItems.begin() + index);

            std::cout << "Предмет успешно куплен и добавлен в инвентарь школы!" << std::endl;
        }
        else {
            std::cout << "Недостаточно золота!" << std::endl;
        }
    } else {
        std::cout << "Неверный номер предмета!" << std::endl;
    }
}

void Market::BuyGladiator(int index, Ludus &school) {
    if (index >= 0 && index < dailyGladiators.size()) {
        int price = dailyGladiators[index]->GetPrice();

        if (school.getGold() >= price) {
            school.SpendGold(price);

            if (school.AddGladiator(std::move(dailyGladiators[index]))) {
                dailyGladiators.erase(dailyGladiators.begin() + index);
                std::cout << "Гладиатор куплен и отправлен в Школу!" << std::endl;
            } else {
                school.SpendGold(-price);
                std::cout << "Школа переполнена! Максимум 5 гладиаторов." << std::endl;
            }
        }
        else {
            std::cout << "Недостаточно золота!" << std::endl;
        }
    } else {
        std::cout << "Неверный номер бойца!" << std::endl;
    }
}