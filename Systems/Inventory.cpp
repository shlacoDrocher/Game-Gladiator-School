
#include "Inventory.h"

void Inventory::AddItem(std::unique_ptr<Item> item) {
    items.push_back(std::move(item));
}

void Inventory::ShowItems() const {
    for (size_t i = 0; i < items.size(); i++) {
        std::cout << i + 1 << ". " << items[i]->GetStats() << std::endl;
    }
}

bool Inventory::IsEmpty() const {
    return items.empty();
}

size_t Inventory::GetSize() const {
    return items.size();
}

std::unique_ptr<Item> Inventory::TakeItem(int index) {
    if (index >= 0 && index < items.size()) {
        auto item = std::move(items[index]);
        items.erase(items.begin() + index);
        return item;
    }
    return nullptr;
}
