//
// Created by Sigma on 09.05.2026.
//

#ifndef CODE_ARENA_H
#define CODE_ARENA_H
#include "CombatStrategies.h"
#include "../Entities/Gladiator.h"


class Arena {
    AccurateAttack strategyAccurate;
    RecklessAttack strategyReckless;
    DefensiveStance strategyDefensive;
public:
    bool StartTournament(Gladiator* playerGladiator, int currentDay);
    bool FightBoss(Gladiator* playerGladiator, Gladiator* boss);
};


#endif //CODE_ARENA_H