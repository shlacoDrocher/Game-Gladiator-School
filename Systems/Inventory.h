#ifndef CODE_INVENTORY_H
#define CODE_INVENTORY_H
#include <vector>
#include <memory>
#include <iostream>
#include "../Entities/Item.h"

class Inventory {
    std::vector<std::unique_ptr<Item>> items;

public:
    void AddItem(std::unique_ptr<Item> item);
    void ShowItems() const;
    [[nodiscard]] bool IsEmpty() const;
    [[nodiscard]] size_t GetSize() const;
    std::unique_ptr<Item> TakeItem(int index);
};

#endif //CODE_INVENTORY_H