
#ifndef CODE_ITEMFACTORY_H
#define CODE_ITEMFACTORY_H
#include <memory>
#include <string>
#include <cstdlib>
#include "../Entities/Item.h"


class ItemFactory {
    public:
    static std::unique_ptr<Item> CreateRandomItem();
};


#endif //CODE_ITEMFACTORY_H