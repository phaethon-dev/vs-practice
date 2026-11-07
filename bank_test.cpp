#include <iostream>
#include <string>
#include <type_traits>
#include <cassert>
#include "bank.h"

// A Bank owns uncopyable accounts, so it should be uncopyable itself
static_assert(!std::is_copy_constructible_v<Bank>, "Bank must not be copyable");

int main()
{
    Bank bank;
    assert(bank.accountCount() == 0);
    assert(bank.totalBalance() == Money(0));

    // Opening accounts
    long long c = bank.openChecking("Chris");
    long long s = bank.openSavings("Sara", 250, Money(10000));   // 2.5%, $100.00 minimum
    assert(bank.accountCount() == 2);
    assert(c != s);

    // Finding accounts
    assert(bank.find(c) != nullptr);
    assert(bank.find(c)->owner() == "Chris");
    assert(bank.find(s)->owner() == "Sara");
    assert(bank.find(c)->typeName() == "Checking");
    assert(bank.find(s)->typeName() == "Savings");
    assert(bank.find(99999) == nullptr);

    // Deposits and withdrawals by account number
    assert(bank.deposit(c, Money(5000)));
    assert(!bank.deposit(c, Money(-1)));          // rejected by the account's own rules
    assert(!bank.deposit(99999, Money(100)));     // no such account
    assert(bank.withdraw(c, Money(1000)));
    assert(bank.find(c)->balance() == Money(4000));
    assert(!bank.withdraw(99999, Money(1)));

    // Savings rules still apply through the bank (polymorphism via unique_ptr<BankAccount>)
    assert(bank.deposit(s, Money(100000)));
    assert(!bank.withdraw(s, Money(95000)));      // would leave $50.00, below the $100.00 minimum
    assert(bank.find(s)->balance() == Money(100000));

    // Transfers
    assert(bank.transfer(c, s, Money(4000)));
    assert(bank.find(c)->balance() == Money(0));
    assert(bank.find(s)->balance() == Money(104000));
    assert(!bank.transfer(c, s, Money(1)));       // insufficient funds

    // A failed transfer must change NOTHING
    bank.deposit(c, Money(2000));
    assert(!bank.transfer(c, 99999, Money(500)));  // destination doesn't exist
    assert(bank.find(c)->balance() == Money(2000));
    assert(!bank.transfer(99999, c, Money(500)));  // source doesn't exist
    assert(bank.find(c)->balance() == Money(2000));
    assert(!bank.transfer(c, c, Money(500)));      // to itself
    assert(bank.find(c)->balance() == Money(2000));

    // Totals
    assert(bank.totalBalance() == Money(106000));  // $20.00 + $1,040.00

    // Month end: only savings earns interest
    Money interest = bank.monthEnd();
    assert(interest == Money(2600));               // 104000 * 250 / 10000
    assert(bank.find(s)->balance() == Money(106600));
    assert(bank.find(c)->balance() == Money(2000));
    assert(bank.totalBalance() == Money(108600));

    // const access
    const Bank &view = bank;
    assert(view.find(c) != nullptr);
    assert(view.find(c)->balance() == Money(2000));
    assert(view.accounts().size() == 2);

    // Print a summary (just to see it work)
    for (const auto &acct : bank.accounts()) {
        std::cout << "#" << acct->accountNumber() << "  "
                  << acct->typeName() << "  "
                  << acct->owner() << "  "
                  << acct->balance() << "\n";
    }
    std::cout << "All tests passed!\n";
    return 0;
}