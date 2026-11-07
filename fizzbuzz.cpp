#include <iostream>
#include <string>
#include <vector>
#include <cassert>
#include <utility>

std::vector<std::string> fizzbuzz(int n, const std::vector<std::pair<int, std::string>> &rules)
{
    std::vector<std::string> result;
    for (int i = 1; i <= n; ++i)
    {
        //string we pushback into the result vector, and a boolean to track if we matched any rules
        std::string value;
        bool matched = false;

        for (const auto &rule : rules)
        {
            if (i % rule.first == 0)
            {
                value += rule.second;
                matched = true;
            }
        }

        if (!matched)
        {
            value = std::to_string(i);
        }

        result.push_back(value);
    }
    return result;
}

int main()
{
    const std::vector<std::pair<int, std::string>> classic = {{3, "Fizz"}, {5, "Buzz"}};
    const std::vector<std::pair<int, std::string>> extended = {{3, "Fizz"}, {5, "Buzz"}, {7, "Bazz"}};

    // Classic rules should still behave exactly as before
    assert(fizzbuzz(0, classic).empty());
    assert(fizzbuzz(1, classic) == std::vector<std::string>{"1"});
    assert(fizzbuzz(15, classic).back() == "FizzBuzz");
    assert(fizzbuzz(15, classic).size() == 15);

    // Extended rules
    assert(fizzbuzz(7, extended).back() == "Bazz");
    assert(fizzbuzz(21, extended).back() == "FizzBazz");
    assert(fizzbuzz(35, extended).back() == "BuzzBazz");
    assert(fizzbuzz(105, extended).back() == "FizzBuzzBazz");

    // No rules at all: every number is just itself
    assert(fizzbuzz(3, {}) == (std::vector<std::string>{"1", "2", "3"}));

    std::cout << "All tests passed!\n";
    return 0;
}