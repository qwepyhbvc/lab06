#include "Transaction.h"
#include <sstream>
#include <iomanip>

Transaction::Transaction(Account* from, Account* to, double amount)
    : fromAccount(from), toAccount(to), amount(amount), completed(false) {
    timestamp = std::chrono::system_clock::now();
}

bool Transaction::execute() {
    if (completed) return false;
    if (fromAccount->withdraw(amount)) {
        if (toAccount->deposit(amount)) {
            completed = true;
            return true;
        } else {
            fromAccount->deposit(amount);
            return false;
        }
    }
    return false;
}

void Transaction::revert() {
    if (!completed) return;
    if (toAccount->withdraw(amount)) {
        fromAccount->deposit(amount);
        completed = false;
    }
}

double Transaction::getAmount() const {
    return amount;
}

bool Transaction::isCompleted() const {
    return completed;
}

std::string Transaction::getTimestamp() const {
    auto time_t = std::chrono::system_clock::to_time_t(timestamp);
    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S");
    return ss.str();
}
