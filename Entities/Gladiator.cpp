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

void Gladiator::ReceiveItem(std::unique_ptr<Item> item) {
    if (auto* weapon = dynamic_cast<Weapon*>(item.get())) {
        EquipWeapon(std::unique_ptr<Weapon>(dynamic_cast<Weapon*>(item.release())));
        std::cout << name << " экипировал новое оружие!" << std::endl;
    }
    else if (auto* armor = dynamic_cast<Armor*>(item.get())) {
        EquipArmor(std::unique_ptr<Armor>(dynamic_cast<Armor*>(item.release())));
        std::cout << name << " надел новую броню!" << std::endl;
    }
    else if (auto* potion = dynamic_cast<Potion*>(item.get())) {
        Heal(potion->GetHealAmount());
        std::cout << name << " выпил зелье и восстановил здоровье!" << std::endl;
    }
}