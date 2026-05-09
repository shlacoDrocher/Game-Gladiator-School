//
// Created by Sigma on 09.05.2026.
//

#ifndef CODE_COMBATSTRATEGIES_H
#define CODE_COMBATSTRATEGIES_H
#include "Gladiator.h"

class ICombatStrategy {
public:
    virtual ~ICombatStrategy() = default;
    virtual void Execute(Gladiator* attacker, Gladiator* defender) = 0;
};

class AccurateAttack : public ICombatStrategy {
public:
    void Execute(Gladiator* attacker, Gladiator* defender) override;
};

class RecklessAttack : public ICombatStrategy {
public:
    void Execute(Gladiator* attacker, Gladiator* defender) override;
};

class DefensiveStance : public ICombatStrategy {
public:
    void Execute(Gladiator* attacker, Gladiator* defender) override;
};

#endif //CODE_COMBATSTRATEGIES_H