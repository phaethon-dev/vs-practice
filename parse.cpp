#include "parse.h"

#include <cctype>
#include <cstddef>

namespace
{
    // True if s is non-empty and every character is a digit
    bool allDigits(const std::string &s)
    {
        if (s.empty())
        {
            return false;
        }
        for (char c : s)
        {
            if (!std::isdigit(static_cast<unsigned char>(c)))
            {
                return false;
            }
        }
        return true;
    }
}

std::string trim(const std::string &text)
{
    std::size_t start = 0;
    while (start < text.size() && std::isspace(static_cast<unsigned char>(text[start])))
    {
        ++start;
    }
    std::size_t end = text.size();
    while (end > start && std::isspace(static_cast<unsigned char>(text[end - 1])))
    {
        --end;
    }
    return text.substr(start, end - start);
}

std::optional<long long> parseInteger(const std::string &text)
{
    std::string s = trim(text);
    if (s.size() > 18 || !allDigits(s)) // 18 digits always fits in a long long
    {
        return std::nullopt;
    }
    return std::stoll(s); // safe: s is 1-18 plain digits
}

std::optional<Money> parseMoney(const std::string &text)
{
    std::string s = trim(text);
    if (!s.empty() && s[0] == '$')
    {
        s = s.substr(1);
    }

    // Split into dollars and (optional) cents at the first '.'
    std::size_t dot = s.find('.');
    bool hasCents = (dot != std::string::npos);
    std::string dollarsPart = hasCents ? s.substr(0, dot) : s;
    std::string centsPart = hasCents ? s.substr(dot + 1) : "";

    // Dollars: 1-15 digits, which leaves room to multiply by 100 without overflow
    if (dollarsPart.size() > 15 || !allDigits(dollarsPart))
    {
        return std::nullopt;
    }
    // Cents, only if there was a '.': 1-2 digits
    if (hasCents && (centsPart.size() > 2 || !allDigits(centsPart)))
    {
        return std::nullopt;
    }

    long long cents = 0;
    if (hasCents)
    {
        cents = std::stoll(centsPart);
        if (centsPart.size() == 1)
        {
            cents *= 10; // "12.3" means 30 cents
        }
    }
    return Money(std::stoll(dollarsPart) * 100 + cents);
}
