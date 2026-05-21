#ifndef CODE_BOOS_H
#define CODE_BOOS_H
#include "Gladiator.h"

class Boss : public Gladiator {
    bool isEnraged; // Состояние Босса
public:
    Boss(std::string name, int hp, int damage, int price)
        : Gladiator(std::move(name), hp, damage, price), isEnraged(false) {}

    void TakeDamage(int damage) override;
};

#endif //CODE_BOOS_H