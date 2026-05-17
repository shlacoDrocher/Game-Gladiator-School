
#ifndef CODE_GLADIATORFACTORY_H
#define CODE_GLADIATORFACTORY_H
#include <memory>

#include "../Entities/Gladiator.h"


class GladiatorFactory {
    public:
    static std::unique_ptr<Gladiator> CreateRandomGladiator(int level);
};


#endif //CODE_GLADIATORFACTORY_H