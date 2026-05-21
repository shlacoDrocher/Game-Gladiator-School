#ifndef CODE_BUILDINGS_H
#define CODE_BUILDINGS_H

class TrainingDummy {
    int level;
public:
    TrainingDummy() : level(1) {}

    [[nodiscard]] int GetLevel() const { return level; }
    [[nodiscard]] int GetUpgradeCost() const { return level * 50; }
    [[nodiscard]] int GetDamageBonus() const { return level * 2; }
    [[nodiscard]] int GetHpBonus() const { return level * 5; }

    void Upgrade() { level++; }
};

class Infirmary {
    int level;
public:
    Infirmary() : level(1) {}

    [[nodiscard]] int GetLevel() const { return level; }
    [[nodiscard]] int GetUpgradeCost() const { return level * 50; }
    [[nodiscard]] int GetHealAmount() const { return level * 15; }

    void Upgrade() { level++; }
};

#endif //CODE_BUILDINGS_H