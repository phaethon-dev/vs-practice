#pragma once
#include <string>
#include <vector>
#include <memory>
#include <cstddef>
#include "account.h"

class Bank
{
public:
    Bank() = default;

    Bank(const Bank &) = delete;
    Bank &operator=(const Bank &) = delete;

    long long openChecking(const std::string &owner);
    long long openSavings(const std::string &owner, long long rateBasisPoints, const Money &minBalance);
    std::size_t accountCount() const;
    BankAccount *find(long long accountNumber);
    const BankAccount *find(long long number) const;
    bool deposit(long long number, const Money &amount);
    bool withdraw(long long number, const Money &amount);
    bool transfer(long long from, long long to, const Money &amount);
    Money totalBalance() const;
    Money monthEnd();
    const std::vector<std::unique_ptr<BankAccount>> &accounts() const;

private:
    std::vector<std::unique_ptr<BankAccount>> accounts_;
};
