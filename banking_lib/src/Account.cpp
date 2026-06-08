#include "Account.h"

Account::Account(const std::string& iban, double initialBalance)
    : iban(iban), balance(initialBalance) {}

bool Account::deposit(double amount) {
    if (amount <= 0) return false;
    balance += amount;
    return true;
}

bool Account::withdraw(double amount) {
    if (amount <= 0 || amount > balance) return false;
    balance -= amount;
    return true;
}

double Account::getBalance() const {
    return balance;
}

std::string Account::getIban() const {
    return iban;
}
