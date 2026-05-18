#ifndef CODE_MARKET_H
#define CODE_MARKET_H
#include "Ludus.h"

class Market {
    std::vector<std::unique_ptr<Item>> dailyItems;
    std::vector<std::unique_ptr<Gladiator>> dailyGladiators;
    public:
    void UpdateAssortment(int currentDay);
    void ShowAssortment() const;
    void BuyItem(int index, Ludus& school);
    void BuyGladiator(int index, Ludus& school);
};

#endif //CODE_MARKET_H