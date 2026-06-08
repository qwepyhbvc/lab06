#pragma once
#include "Account.h"
#include <chrono>
#include <string>

class Transaction {
private:
    Account* fromAccount;
    Account* toAccount;
    double amount;
    std::chrono::system_clock::time_point timestamp;
    bool completed;
    
public:
    Transaction(Account* from, Account* to, double amount);
    
    bool execute();
    void revert();
    double getAmount() const;
    bool isCompleted() const;
    std::string getTimestamp() const;
};
