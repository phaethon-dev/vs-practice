#include "savings.h"

SavingsAccount::SavingsAccount(const std::string &owner, long long interestRate, const Money &minimumBalance)
    : BankAccount(owner), interestRate_(interestRate), minimumBalance_(minimumBalance) {}

long long SavingsAccount::interestRate() const
{
    return interestRate_;
}

const Money &SavingsAccount::minimumBalance() const
{
    return minimumBalance_;
}

bool SavingsAccount::withdraw(const Money &amount)
{

    if ((balance() - amount) < minimumBalance_)
    {
        return false;
    }
    return BankAccount::withdraw(amount);
}

std::string SavingsAccount::typeName() const
{
    return "Savings";
}

Money SavingsAccount::monthEnd()
{
    return applyInterest();
}

Money SavingsAccount::applyInterest()
{
    Money interest = (balance() * interestRate_) / 10000;
    if (interest > Money(0))
    {
        deposit(interest);
    }
    return interest;
}