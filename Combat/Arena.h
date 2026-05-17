
#ifndef CODE_ARENA_H
#define CODE_ARENA_H
#include "CombatStrategies.h"
#include "../Entities/Gladiator.h"


class Arena {
public:
    bool StartTournament(Gladiator* playerGladiator, int currentDay);
    bool FightBoss(Gladiator* playerGladiator, Gladiator* boss);
};


#endif //CODE_ARENA_H