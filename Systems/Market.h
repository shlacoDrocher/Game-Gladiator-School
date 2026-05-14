//
// Created by Sigma on 06.05.2026.
//

#ifndef CODE_MARKET_H
#define CODE_MARKET_H
#include "../Factories/ItemFactory.h"
#include "../Factories/GladiatorFactory.h"
#include "Ludus.h"

class Market {
    std::vector<std::unique_ptr<Item>> dailyItems;
    std::vector<std::unique_ptr<Gladiator>> dailyGladiators;
    public:
    void UpdateAssortment();
    void ShowAssortment() const;
    void BuyItem(int index, Ludus& school);
    void BuyGladiator(int index, Ludus& school);
};


#endif //CODE_MARKET_H