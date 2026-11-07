#pragma once

#include <string>
#include <vector>
#include "money.h"

class BankAccount
{
public:
    explicit BankAccount(const std::string &owner);
    virtual ~BankAccount() = default;
    
    virtual Money monthEnd();  // default implementation does nothing
    virtual std::string typeName() const; // default implementation returns "Checking"

    BankAccount(const BankAccount &) = delete;
    BankAccount &operator=(const BankAccount &) = delete;

    const std::string &owner() const;
    Money balance() const;
    long long accountNumber() const;
    bool deposit(const Money &amount);
    virtual bool withdraw(const Money &amount);
    bool transferTo(BankAccount &other, const Money &amount);
    const std::vector<Money> &history() const;

private:
    static long long nextNumber_;
    const long long accountNumber_;
    std::vector<Money> history_;
    std::string owner_;
    Money balance_;
};