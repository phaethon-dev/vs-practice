#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>
#include "money.h"

// Prints a Money into a string, so the output can be checked with assert
std::string show(const Money &m)
{
    std::ostringstream out;
    out << m;
    return out.str();
}

int main()
{
    // Construction
    Money zero;
    Money price(1234);                       // $12.34
    assert(zero.cents() == 0);
    assert(price.cents() == 1234);

    // Arithmetic
    assert((price + Money(66)).cents() == 1300);
    assert((price - Money(234)).cents() == 1000);
    assert((-price).cents() == -1234);
    assert((price * 3).cents() == 3702);
    assert((3 * price).cents() == 3702);     // the reversed order works too

    // Compound assignment changes the left side
    Money wallet(1000);
    wallet += Money(500);
    assert(wallet.cents() == 1500);
    wallet -= Money(2000);
    assert(wallet.cents() == -500);

    // Chaining works like it does for ints
    Money a(100), b(200), c(300);
    a += b += c;                             // b becomes 500, then a becomes 600
    assert(b.cents() == 500 && a.cents() == 600);

    // Comparisons
    assert(Money(500) == Money(500));
    assert(Money(500) != Money(501));
    assert(Money(100) < Money(200));
    assert(Money(200) > Money(100));
    assert(Money(100) <= Money(100));
    assert(Money(100) >= Money(100));
    assert(!(Money(200) < Money(100)));

    // operator< makes standard algorithms work with no lambda
    std::vector<Money> prices = {Money(999), Money(50), Money(2500), Money(100)};
    std::sort(prices.begin(), prices.end());
    assert(prices.front() == Money(50));
    assert(prices.back() == Money(2500));
    assert(std::max(Money(10), Money(20)) == Money(20));

    // Printing
    assert(show(Money(1234)) == "$12.34");
    assert(show(Money(5)) == "$0.05");       // leading zero on the cents
    assert(show(Money(10000)) == "$100.00");
    assert(show(Money(0)) == "$0.00");
    assert(show(Money(-507)) == "-$5.07");   // the minus sign goes before the $

    // Chained printing
    std::ostringstream line;
    line << "Total: " << Money(4250) << " (paid)";
    assert(line.str() == "Total: $42.50 (paid)");

    // Money is a value type: copying is fine and independent
    Money original(700);
    Money copy = original;
    copy += Money(1);
    assert(original.cents() == 700);
    assert(copy.cents() == 701);

    std::cout << "Everything costs " << Money(1999) << "\n";
    std::cout << "All tests passed!\n";
    return 0;
}