#include "account.h"

long long BankAccount::nextNumber_ = 1;

BankAccount::BankAccount(const std::string &owner) : accountNumber_(nextNumber_++), owner_(owner), balance_(Money(0)) {}

std::string BankAccount::typeName() const
{
    return "Checking";  // default implementation returns "Checking"
}

Money BankAccount::monthEnd()
{
    return Money(0);   // a plain account earns nothing at month end
}

const std::string &BankAccount::owner() const
{
    return owner_;
}

Money BankAccount::balance() const
{
    return balance_;
}

long long BankAccount::accountNumber() const
{
    return accountNumber_;
}

bool BankAccount::deposit(const Money &amount)
{
    if (amount.cents() > 0)
    {
        balance_ += amount;
        history_.push_back(amount);
        return true;
    }
    return false;
}

bool BankAccount::withdraw(const Money &amount)
{
    if (amount.cents() > 0 && amount.cents() <= balance_.cents())
    {
        balance_ -= amount;
        history_.push_back(-amount);
        return true;
    }
    return false;
}

bool BankAccount::transferTo(BankAccount &other, const Money &amount)
{
    if (withdraw(amount))
    {
        other.deposit(amount);
        return true;
    }
    return false;
}

const std::vector<Money> &BankAccount::history() const
{
    return history_;
}