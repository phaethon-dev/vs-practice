#include "money.h"
#include <cstdlib>

Money::Money(long long cents) : cents_(cents) {}

long long Money::cents() const
{
    return cents_;
}

Money Money::operator+(const Money &other) const
{
    return Money(cents_ + other.cents_);
}

Money Money::operator-(const Money &other) const
{
    return Money(cents_ - other.cents_);
}

Money Money::operator+() const
{
    return Money(+cents_);
}

Money Money::operator-() const
{
    return Money(-cents_);
}

Money Money::operator*(long long factor) const
{
    return Money(cents_ * factor);
}

Money Money::operator/(long long factor) const
{
    return Money(cents_ / factor);
}

Money operator*(long long factor, const Money &m)
{
    return m * factor;
}

Money operator/(long long factor, const Money &m)
{
    return m / factor;
}

Money &Money::operator+=(const Money &other)
{
    cents_ += other.cents_;
    return *this;
}

Money &Money::operator-=(const Money &other)
{
    cents_ -= other.cents_;
    return *this;
}

bool Money::operator==(const Money &other) const
{
    return cents_ == other.cents_;
}

bool Money::operator!=(const Money &other) const
{
    return !(*this == other);
}

bool Money::operator<(const Money &other) const
{
    return cents_ < other.cents_;
}

bool Money::operator>(const Money &other) const
{
    return cents_ > other.cents_;
}

bool Money::operator<=(const Money &other) const
{
    return cents_ <= other.cents_;
}

bool Money::operator>=(const Money &other) const
{
    return cents_ >= other.cents_;
}

std::ostream &operator<<(std::ostream &out, const Money &m)
{
    long long total = m.cents();
    long long amount = std::abs(total);
    long long dollars = amount / 100;
    long long cents = amount % 100;

    if (total < 0)
    {
        out << "-";
    }
    out << "$" << dollars << "." << (cents < 10 ? "0" : "") << cents;
    return out;
}