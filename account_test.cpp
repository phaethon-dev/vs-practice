#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "account.h"

static_assert(!std::is_copy_constructible_v<BankAccount>, "BankAccount must not be copyable");
static_assert(!std::is_copy_assignable_v<BankAccount>, "BankAccount must not be copy-assignable");

int main()
{
    BankAccount alice("Alice");
    BankAccount bob("Bob");

    // Starts empty
    assert(alice.owner() == "Alice");
    assert(alice.balance() == Money(0));
    assert(alice.history().empty());

    // Deposits
    assert(alice.deposit(Money(5000)));          // $50.00
    assert(alice.deposit(Money(1234)));          // $12.34
    assert(alice.balance() == Money(6234));        // $62.34

    // Invalid deposits change nothing
    assert(!alice.deposit(Money(0)));
    assert(!alice.deposit(Money(-100)));
    assert(alice.balance() == Money(6234));

    // Withdrawals
    assert(alice.withdraw(Money(234)));          // $2.34
    assert(alice.balance() == Money(6000));        // $60.00   
    assert(!alice.withdraw(Money(6001)));        // more than the balance
    assert(!alice.withdraw(Money(-5)));
    assert(alice.balance() == Money(6000));
    assert(alice.withdraw(Money(6000)));         // exactly everything is allowed
    assert(alice.balance() == Money(0));

    // History records only successful changes, in order
    assert(alice.history() == (std::vector<Money>{Money(5000), Money(1234), Money(-234), Money(-6000)}));

    // Transfers
    alice.deposit(Money(10000));
    assert(alice.transferTo(bob, Money(2500)));
    assert(alice.balance() == Money(7500));
    assert(bob.balance() == Money(2500));

    // Failed transfers change NEITHER account
    assert(!alice.transferTo(bob, Money(999999)));
    assert(!alice.transferTo(bob, Money(0)));
    assert(alice.balance() == Money(7500));
    assert(bob.balance() == Money(2500));

    // Both histories recorded the transfer
    assert(alice.history().back() == Money(-2500));
    assert(bob.history() == (std::vector<Money>{Money(2500)}));

    // const correctness
    const BankAccount &view = alice;
    assert(view.balance() == Money(7500));
    assert(view.history().size() == 6);

    // Account numbers are assigned in creation order
    assert(alice.accountNumber() == 1);
    assert(bob.accountNumber() == 2);

    BankAccount carol("Carol");
    BankAccount dave("Dave");
    assert(carol.accountNumber() == 3);
    assert(dave.accountNumber() == 4);

    // Each account keeps its own number
    assert(alice.accountNumber() == 1);

    std::cout << "All tests passed!\n";
    return 0;
}