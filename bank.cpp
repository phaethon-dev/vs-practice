#include "bank.h"
#include "savings.h"

long long Bank::openChecking(const std::string &owner)
{
    auto account = std::make_unique<BankAccount>(owner);
    long long number = account->accountNumber();
    accounts_.push_back(std::move(account));
    return number;
}

long long Bank::openSavings(const std::string &owner, long long rateBasisPoints, const Money &minBalance)
{
    auto account = std::make_unique<SavingsAccount>(owner, rateBasisPoints, minBalance);
    long long number = account->accountNumber();
    accounts_.push_back(std::move(account));
    return number;
}

std::size_t Bank::accountCount() const
{
    return accounts_.size();
}

BankAccount *Bank::find(long long accountNumber)
{
    for (const auto &account : accounts_)
    {
        if (account->accountNumber() == accountNumber)
        {
            return account.get();
        }
    }
    return nullptr;
}

const BankAccount *Bank::find(long long number) const
{
    for (const auto &account : accounts_)
    {
        if (account->accountNumber() == number)
        {
            return account.get();
        }
    }
    return nullptr;
}

bool Bank::deposit(long long number, const Money &amount)
{
    auto account = find(number);
    if (!account)
    {
        return false;
    }
    return account->deposit(amount);
}

bool Bank::withdraw(long long number, const Money &amount)
{
    auto account = find(number);
    if (!account)
    {
        return false;
    }
    return account->withdraw(amount);
}

bool Bank::transfer(long long from, long long to, const Money &amount)
{
    auto fromAccount = find(from);
    auto toAccount = find(to);
    if (!fromAccount || !toAccount || from == to)
    {
        return false;
    }
    return fromAccount->transferTo(*toAccount, amount);
}

Money Bank::totalBalance() const
{
    Money total(0);
    for (const auto &account : accounts_)
    {
        total += account->balance();
    }
    return total;
}

Money Bank::monthEnd()
{
    Money total(0);
    for (const auto &account : accounts_)
    {
        total += account->monthEnd();
    }
    return total;
}

const std::vector<std::unique_ptr<BankAccount>> &Bank::accounts() const
{
    return accounts_;
}