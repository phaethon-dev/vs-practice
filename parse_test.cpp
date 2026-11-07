#include <iostream>
#include <optional>
#include <string>
#include <cassert>
#include "parse.h"

int main()
{
    // ---- trim ----
    assert(trim("  hello  ") == "hello");
    assert(trim("hello") == "hello");
    assert(trim("") == "");
    assert(trim("     ") == "");
    assert(trim("\t tabs and newlines \n") == "tabs and newlines");
    assert(trim("  inner  spaces stay  ") == "inner  spaces stay");

    // ---- parseInteger ----
    assert(parseInteger("42") == 42); // optional == value: true only if it holds 42
    assert(parseInteger("  7  ") == 7);
    assert(parseInteger("0") == 0);
    assert(parseInteger("007") == 7);

    assert(!parseInteger("")); // empty optional
    assert(!parseInteger("   "));
    assert(!parseInteger("abc"));
    assert(!parseInteger("12abc")); // std::stoi would have returned 12 here
    assert(!parseInteger("-5"));
    assert(!parseInteger("4.2"));
    assert(!parseInteger("1 2"));
    assert(!parseInteger("1234567890123456789")); // 19 digits: too long

    // ---- parseMoney: accepted ----
    assert(parseMoney("12.34") == Money(1234));
    assert(parseMoney("12") == Money(1200));
    assert(parseMoney("12.3") == Money(1230)); // one decimal digit means tens of cents
    assert(parseMoney("0.05") == Money(5));
    assert(parseMoney("$5.00") == Money(500));
    assert(parseMoney("  7.25  ") == Money(725));
    assert(parseMoney("0") == Money(0));
    assert(parseMoney("$1000") == Money(100000));

    // ---- parseMoney: rejected ----
    assert(!parseMoney(""));
    assert(!parseMoney("   "));
    assert(!parseMoney("abc"));
    assert(!parseMoney("12.345"));
    assert(!parseMoney("-5"));
    assert(!parseMoney("12."));
    assert(!parseMoney(".50"));
    assert(!parseMoney("1.2.3"));
    assert(!parseMoney("12a"));
    assert(!parseMoney("$"));
    assert(!parseMoney("$-5"));
    assert(!parseMoney("1,000.00"));
    assert(!parseMoney("$$5"));
    assert(!parseMoney("1234567890123456.00")); // 16 dollar digits: too long

    assert(!parseMoney("12 .50"));
    assert(!parseMoney("12. 5"));
    assert(!parseMoney("$ 5"));
    assert(!parseMoney("+5"));
    assert(!parseMoney("12.+5"));
    assert(!parseInteger("+5"));

    // ---- using optional the way the menu will ----
    std::string input = "25.50";
    if (auto amount = parseMoney(input))
    {
        std::cout << "Parsed " << input << " as " << *amount << "\n";
    }
    else
    {
        assert(false); // should never happen for this input
    }

    std::cout << "All tests passed!\n";
    return 0;
}