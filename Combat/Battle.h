#ifndef CODE_BATTLE_H
#define CODE_BATTLE_H
#include "../Entities/Gladiator.h"
#include "CombatStrategies.h"
#include <memory>

class Battle {
    Gladiator* player;
    Gladiator* enemy;
    int roundCount;

    std::unique_ptr<ICombatStrategy> CreateStrategy(int choice);

public:
    Battle(Gladiator* p, Gladiator* e);
    bool Start();
};

#endif //CODE_BATTLE_H