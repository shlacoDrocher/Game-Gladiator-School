#include "CombatStrategies.h"
#include <cstdlib>
#include <iostream>

void AccurateAttack::Execute(Gladiator* attacker, Gladiator* defender) {
    int damage = attacker->GetTotalDamage();
    std::cout << "Боец " << attacker->GetName() << " наносит точный удар!" << std::endl;
    defender->TakeDamage(damage);
}

void RecklessAttack::Execute(Gladiator* attacker, Gladiator* defender) {
    int chance = rand() % 100;
    if (chance < 60) {
        int damage = static_cast<int>(attacker->GetTotalDamage() * 2.5f);
        std::cout << "Боец " << attacker->GetName() << " наносит сокрушительный удар!" << std::endl;
        defender->TakeDamage(damage);
    }
    else {
        std::cout << "Боец " << attacker->GetName() << " промахнулся!" << std::endl;
    }
    attacker->SetVulnerable(true);
}

void DefensiveStance::Execute(Gladiator* attacker, Gladiator* defender) {
    std::cout << "Боец " << attacker->GetName() << " уходит в глухую защиту и переводит дыхание." << std::endl;
    attacker->SetBlocking(true);
    int healAmount = static_cast<int>(attacker->GetMaxHp() * 0.30f);
    attacker->Heal(healAmount);
}