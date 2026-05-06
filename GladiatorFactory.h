//
// Created by Sigma on 06.05.2026.
//

#ifndef CODE_GLADIATORFACTORY_H
#define CODE_GLADIATORFACTORY_H
#include <memory>

#include "Gladiator.h"


class GladiatorFactory {
    public:
    static std::unique_ptr<Gladiator> CreateRandomGladiator();
};


#endif //CODE_GLADIATORFACTORY_H