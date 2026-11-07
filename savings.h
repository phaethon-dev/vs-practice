#pragma once

#include <string>
#include "account.h"

class SavingsAccount : public BankAccount
{
    public:
        SavingsAccount(const std::string &owner, long long interestRate, const Money &minimumBalance);
        long long interestRate() const;
        const Money &minimumBalance() const;
        bool withdraw(const Money &amount) override;
        std::string typeName() const override;
        Money monthEnd() override;
        Money applyInterest();
    private:
        const long long interestRate_;
        const Money minimumBalance_;
};