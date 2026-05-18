#ifndef CODE_ARENA_H
#define CODE_ARENA_H
#include "CombatStrategies.h"
#include "../Entities/Gladiator.h"

class Arena {
    static bool ExecuteBattle(Gladiator* player, Gladiator* enemy);
    static std::unique_ptr<ICombatStrategy> CreateStrategy(int choice);
public:
    static bool StartTournament(Gladiator* playerGladiator, int currentDay);
    static bool FightBoss(Gladiator* playerGladiator, Gladiator* boss);
};

#endif //CODE_ARENA_H