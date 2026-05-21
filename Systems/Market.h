#ifndef CODE_MARKET_H
#define CODE_MARKET_H
#include "Ludus.h"

enum class TransactionResult {
    SUCCESS,
    INSUFFICIENT_FUNDS,
    LUDUS_FULL,
    INVALID_INDEX
};

class Market {
    std::vector<std::unique_ptr<Item>> dailyItems;
    std::vector<std::unique_ptr<Gladiator>> dailyGladiators;
public:
    void UpdateAssortment(int currentDay);
    void ShowAssortment() const;
    TransactionResult BuyItem(int index, Ludus& school);
    TransactionResult BuyGladiator(int index, Ludus& school);
};

#endif //CODE_MARKET_H