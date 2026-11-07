#include <iostream>
#include <vector>
#include <cassert>
#include "account.h"
#include "savings.h"

static_assert(!std::is_copy_constructible_v<SavingsAccount>, "SavingsAccount must not be copyable");
static_assert(!std::is_copy_assignable_v<SavingsAccount>, "SavingsAccount must not be copy-assignable");

// Works with ANY kind of account, through a base-class reference
bool tryWithdraw(BankAccount &account, const Money &amount)
{
    return account.withdraw(amount);
}

int main()
{
    BankAccount checking("Chris");
    SavingsAccount savings("Sara", 250, Money(10000));   // 2.5% interest, $100.00 minimum

    // Inherited behavior works as-is
    assert(savings.owner() == "Sara");
    assert(savings.balance() == Money(0));
    assert(savings.interestRate() == 250);
    assert(savings.minimumBalance() == Money(10000));

    // Account numbers are shared across both classes (same static counter)
    assert(checking.accountNumber() == 1);
    assert(savings.accountNumber() == 2);

    // Deposits are inherited
    assert(savings.deposit(Money(100000)));               // $1,000.00

    // The minimum balance rule
    assert(!savings.withdraw(Money(95000)));              // would leave $50.00, below $100.00
    assert(savings.balance() == Money(100000));           // unchanged
    assert(savings.withdraw(Money(90000)));               // leaves exactly $100.00, which is allowed
    assert(savings.balance() == Money(10000));
    assert(!savings.withdraw(Money(0)));                  // base rules still apply
    assert(!savings.withdraw(Money(-5)));

    // Interest
    savings.deposit(Money(990000));                       // balance: $10,000.00
    assert(savings.applyInterest() == Money(25000));      // 2.5% = $250.00
    assert(savings.balance() == Money(1025000));
    assert(savings.history().back() == Money(25000));     // recorded like a deposit

    // Tiny balances earn no interest (integer division rounds down), and nothing is recorded
    SavingsAccount tiny("Tim", 250, Money(0));
    tiny.deposit(Money(39));
    auto before = tiny.history().size();
    assert(tiny.applyInterest() == Money(0));             // 39 * 250 / 10000 = 0
    assert(tiny.balance() == Money(39));
    assert(tiny.history().size() == before);

    // Polymorphism 1: transferTo (written in BankAccount!) uses the savings rules
    assert(!savings.transferTo(checking, Money(1020000))); // would leave $50.00
    assert(savings.balance() == Money(1025000));
    assert(checking.balance() == Money(0));
    assert(savings.transferTo(checking, Money(15000)));
    assert(checking.balance() == Money(15000));

    // Polymorphism 2: through a base-class reference, the savings rules still apply
    Money all = savings.balance();
    assert(!tryWithdraw(savings, all));            // would empty it, below the minimum
    assert(tryWithdraw(checking, Money(15000)));          // a regular account has no minimum
    assert(checking.balance() == Money(0));

    std::cout << "All tests passed!\n";
    return 0;
}