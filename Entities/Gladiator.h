#ifndef CODE_GLADIATOR_H
#define CODE_GLADIATOR_H
#include <memory>
#include "Item.h"
#include <string>

class Gladiator
{
    std::string name;
    int baseHP;
    int hp;
    int baseDamage;
    int price;
    std::unique_ptr<Weapon> equipwepon;
    std::unique_ptr<Armor> equiparmon;
    bool hasTrainedToday;
    bool hasFoughtToday;
    bool isVulnerable;
    bool isBlocking;
    public:
    Gladiator(std::string name, int hp, int damage, int price) : name(std::move(name)), baseHP(hp), hp(hp), baseDamage(damage), price(price){
        hasTrainedToday = false;
        hasFoughtToday = false;
        isVulnerable = false;
        isBlocking = false;
    }
    virtual ~Gladiator() = default;
    std::string GetName() { return name; }
    [[nodiscard]] int GetPrice() const { return price; }
    [[nodiscard]] int GetHp() const { return hp; }

    [[nodiscard]] int GetMaxHp () const
    {
        int armorBonus = (equiparmon != nullptr) ? equiparmon->GetHpBonus() : 0;
        return baseHP + armorBonus;
    }
    [[nodiscard]] int GetTotalDamage() const
    {
        int damage = (equipwepon != nullptr) ? equipwepon->GetDamage() : 0;
        return baseDamage + damage;
    }
    void EquipWeapon(std::unique_ptr<Weapon> weapon) {equipwepon = std::move(weapon);}
    void EquipArmor(std::unique_ptr<Armor> armor) {
        int bonus = armor->GetHpBonus();
        equiparmon = std::move(armor);
        hp += bonus;
        if (hp > GetMaxHp()) {
            hp = GetMaxHp();
        }
    }

    void Heal(int amount);
    virtual void TakeDamage(int damage);
    void SetVulnerable(bool val) { isVulnerable = val;}
    void SetBlocking(bool val) { isBlocking = val;}
    [[nodiscard]] bool HasTrainedToday() const { return hasTrainedToday; }
    void SetTrainedToday(bool val) { hasTrainedToday = val; }
    void AddBaseDamage(int amount) { baseDamage += amount; }
    void AddBaseHp(int amount) {
        baseHP += amount;
        hp += amount;
    }
    void ReceiveItem(std::unique_ptr<Item> item);
};

#endif //CODE_GLADIATOR_H