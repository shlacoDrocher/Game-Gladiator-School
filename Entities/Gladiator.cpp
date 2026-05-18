#include "Gladiator.h"

void Gladiator::Heal(int amount)
{
    hp = hp + amount;
    if (hp > GetMaxHp()) {hp = GetMaxHp();}
}

void Gladiator::TakeDamage(int damage)
{
    auto finalDamage = static_cast<float>(damage);

    if (isBlocking == true) {finalDamage = finalDamage * 0.3f;}

    if (isVulnerable == true) {
        finalDamage = finalDamage * 1.5f;
    }

    hp = hp - static_cast<int>(finalDamage);

    if (hp < 0) {hp = 0;}
}