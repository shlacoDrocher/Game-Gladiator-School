#ifndef CODE_TREASURY_H
#define CODE_TREASURY_H

class Treasury {
    int balance;
public:
    Treasury(int startMoney = 200) : balance(startMoney) {}

    [[nodiscard]] int GetBalance() const { return balance; }

    void AddFunds(int amount) { balance += amount; }

    bool SpendFunds(int amount) {
        if (balance >= amount) {
            balance -= amount;
            return true;
        }
        return false;
    }
};

#endif //CODE_TREASURY_H