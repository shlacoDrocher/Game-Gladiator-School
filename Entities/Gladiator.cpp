#include "Gladiator.h"
#include <algorithm>

void Gladiator::Heal(int amount)
{
    hp = std::min(hp + amount, GetMaxHp());
}

void Gladiator::TakeDamage(int damage)
{
    auto finalDamage = static_cast<float>(damage);

    if (isBlocking == true) {finalDamage = finalDamage * 0.3f;}

    if (isVulnerable == true) {
        finalDamage = finalDamage * 1.5f;
    }

    hp = std::max(hp - static_cast<int>(finalDamage), 0);
}