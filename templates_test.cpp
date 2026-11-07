#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include "algorithms.h"
#include "stack.h"
#include "money.h"

int main()
{
    // ---- Part A: function templates ----

    // int
    std::vector<int> nums = {4, 9, 2, 7};
    assert(maxOf(nums) == 9);
    assert(sumOf(nums) == 22);
    assert(sumOf(std::vector<int>{}) == 0);

    // double
    std::vector<double> prices = {1.5, 2.5, 0.25};
    assert(maxOf(prices) == 2.5);
    assert(sumOf(prices) == 4.25);

    // std::string: < is alphabetical, + joins strings
    std::vector<std::string> words = {"pear", "apple", "zebra", "mango"};
    assert(maxOf(words) == "zebra");
    assert(sumOf(words) == "pearapplezebramango");

    // Your own Money type works too, thanks to its operators
    std::vector<Money> bills = {Money(500), Money(1999), Money(250)};
    assert(maxOf(bills) == Money(1999));
    assert(sumOf(bills) == Money(2749));
    assert(sumOf(std::vector<Money>{}) == Money(0));

    // maxOf returns a reference to the actual element, not a copy
    assert(&maxOf(nums) == &nums[1]);

    // Explicit template argument
    assert(maxOf<int>(nums) == 9);

    // ---- Part B: class template ----

    Stack<int> s;
    assert(s.empty());
    assert(s.size() == 0);
    s.push(1);
    s.push(2);
    s.push(3);
    assert(!s.empty());
    assert(s.size() == 3);
    assert(s.top() == 3);
    s.pop();
    assert(s.top() == 2);
    assert(s.size() == 2);

    Stack<std::string> names;
    names.push("first");
    names.push("second");
    assert(names.top() == "second");

    Stack<Money> payments;
    payments.push(Money(100));
    payments.push(Money(250));
    assert(payments.top() == Money(250));

    // const correctness
    const Stack<int> &view = s;
    assert(view.top() == 2);
    assert(view.size() == 2);

    // Last in, first out
    Stack<char> letters;
    for (char c : std::string("abc")) {
        letters.push(c);
    }
    std::string reversed;
    while (!letters.empty()) {
        reversed += letters.top();
        letters.pop();
    }
    assert(reversed == "cba");

    std::cout << "Total bills: " << sumOf(bills) << "\n";
    std::cout << "All tests passed!\n";
    return 0;
}