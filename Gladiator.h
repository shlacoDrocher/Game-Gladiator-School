//
// Created by New on 02.05.2026.
//

#ifndef CODE_GLADIATOR_H
#define CODE_GLADIATOR_H
#include "Item.h"
#include <string>

class Gladiator
{
    std::string name;
    int baseHP;
    int hp;
    int baseDamage;
    Weapon* equipwepon;
    Armor* equiparmon;
    bool hasTrainedToday;
    bool hasFoughtToday;
    bool isVulnerable;
    bool isBlocking;
    public:
    Gladiator(std::string name, int hp, int damage) : name(std::move(name)), baseHP(hp), hp(hp), baseDamage(damage){
        equiparmon = nullptr;
        equipwepon = nullptr;
        hasTrainedToday = false;
        hasFoughtToday = false;
        isVulnerable = false;
        isBlocking = false;
    }
    std::string GetName() { return name; }
    int GetHp() const { return hp; }

    int GetMaxHp () const
    {
        int armorBonus = (equiparmon != nullptr) ? equiparmon->GetHpBonus() : 0;
        return baseHP + armorBonus;
    }
    int GetTotalDamage() const
    {
        int damage = (equipwepon != nullptr) ? equipwepon->GetDamage() : 0;
        return baseDamage + damage;
    }
    void EquipWeapon(Weapon* weapon) {equipwepon = weapon;}
    void EquipArmor(Armor* armor) {equiparmon = armor;}
    void Heal(int amount);
    void TakeDamage(int damage);
    void SetVulnerable(bool val) { isVulnerable = val;}
    void SetBlocking(bool val)
    { isBlocking = val;}
};

#endif //CODE_GLADIATOR_H
