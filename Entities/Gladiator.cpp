#include "Gladiator.h"
#include <algorithm>
#include "Boss.h"
#include "iostream"

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

void Boss::TakeDamage(int damage) {
    Gladiator::TakeDamage(damage);
    if (!isEnraged && GetHp() <= GetMaxHp() / 2) {
        isEnraged = true;
        AddBaseDamage(15);
        std::cout << "\n[!!!] " << GetName() << " ВПАДАЕТ В ЯРОСТЬ! Его атаки становятся смертоносными!" << std::endl;
    }
}