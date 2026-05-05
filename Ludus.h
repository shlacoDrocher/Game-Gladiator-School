//
// Created by Sigma on 05.05.2026.
//

#ifndef CODE_LUDUS_H
#define CODE_LUDUS_H
#include <memory>

#include "Gladiator.h"
#include <vector>


class Ludus {
    int gold = 150;
    int reputation = 0;
    int dummyLevel = 1;
    int infirmaryLevel = 1;
    std::vector<std::unique_ptr<Gladiator>> gladiators;
    public:
    Ludus() = default;
    [[nodiscard]] int getGold() const { return gold; }
    [[nodiscard]] int getReputation() const { return reputation; }
    bool AddGladiator(std::unique_ptr<Gladiator> g);
    void ShowRoster() const;
    void TrainGladiator(int index);
    void UpgradeDummy();
    void UpgradeInfirmary();
    void NightHeal();
};
#endif //CODE_LUDUS_H