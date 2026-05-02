#include <iostream>
#include <string>

class Item {
    std::string name;
    int price;
    public:
    Item(std::string name, int price) : name(name), price(price) {}
    virtual ~Item() {}
    virtual std::string GetStats() = 0;
};



