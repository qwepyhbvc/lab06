#pragma once
#include <string>

class Account {
private:
    std::string iban;
    double balance;
    
public:
    Account(const std::string& iban, double initialBalance = 0.0);
    
    bool deposit(double amount);
    bool withdraw(double amount);
    double getBalance() const;
    std::string getIban() const;
};
