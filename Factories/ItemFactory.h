#ifndef CODE_ITEMFACTORY_H
#define CODE_ITEMFACTORY_H
#include <memory>
#include <string>
#include <cstdlib>
#include "../Entities/Item.h"

class ItemFactory {
public:
    virtual ~ItemFactory() = default;
    virtual std::unique_ptr<Item> CreateItem() const = 0;
};

class WeaponFactory : public ItemFactory {
public:
    std::unique_ptr<Item> CreateItem() const override;
};

class ArmorFactory : public ItemFactory {
public:
    std::unique_ptr<Item> CreateItem() const override;
};

class PotionFactory : public ItemFactory {
public:
    std::unique_ptr<Item> CreateItem() const override;
};

#endif //CODE_ITEMFACTORY_H