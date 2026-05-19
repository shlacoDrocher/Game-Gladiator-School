#ifndef CODE_ARENA_H
#define CODE_ARENA_H
#include "CombatStrategies.h"
#include "../Entities/Gladiator.h"

class Arena {
    bool ExecuteBattle(Gladiator* player, Gladiator* enemy);
    std::unique_ptr<ICombatStrategy> CreateStrategy(int choice);
public:
    bool StartTournament(Gladiator* playerGladiator, int currentDay);
    bool FightBoss(Gladiator* playerGladiator, Gladiator* boss);
};

#endif //CODE_ARENA_H