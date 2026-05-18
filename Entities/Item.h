#ifndef CODE_ITEM_H
#define CODE_ITEM_H
#include <string>

class Item {
protected:
    std::string name;
    int price;
public:
    Item(std::string name, int price) : name(std::move(name)), price(price) {}
    virtual ~Item() = default;
    virtual std::string GetStats() = 0;

    std::string GetName() { return name; }
    [[nodiscard]] int GetPrice() const { return price; }
};

class Weapon : public Item {
    int damageWeapon;
public:
    Weapon(const std::string& name, int price, int damage) : Item(name, price), damageWeapon(damage) {}
    std::string GetStats() override {
        return name + " [Оружие] (Урон: +" + std::to_string(damageWeapon) + ") Цена: " + std::to_string(price);
    }

    [[nodiscard]] int GetDamage() const { return damageWeapon; }
};

class Armor : public Item {
    int hpBonus;
public:
    Armor(const std::string& name, int price, int hp) : Item(name, price), hpBonus(hp) {}
    std::string GetStats() override {
        return name + " [Броня] (Макс. ХП: +" + std::to_string(hpBonus) + ") Цена: " + std::to_string(price);
    }

    [[nodiscard]] int GetHpBonus() const { return hpBonus; }
};

class Potion : public Item {
    int healAmount;
public:
    Potion(const std::string& name, int price, int heal) : Item(name, price), healAmount(heal) {}
    std::string GetStats() override {
        return name + " [Зелье] (Лечение: +" + std::to_string(healAmount) + ") Цена: " + std::to_string(price);
    }

    [[nodiscard]] int GetHealAmount() const { return healAmount; }
};

#endif //CODE_ITEM_H