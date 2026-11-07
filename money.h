#pragma once

#include <ostream>

class Money
{
    public:
        explicit Money(long long cents = 0);
        long long cents() const;

        Money operator+(const Money &other) const;
        Money operator-(const Money &other) const;
        Money operator+() const;
        Money operator-() const;
        Money operator*(long long factor) const;
        Money operator/(long long factor) const;

        Money &operator+=(const Money &other);
        Money &operator-=(const Money &other);

        bool operator==(const Money &other) const;
        bool operator!=(const Money &other) const;
        bool operator<(const Money &other) const;
        bool operator>(const Money &other) const;
        bool operator<=(const Money &other) const;
        bool operator>=(const Money &other) const;

        friend std::ostream &operator<<(std::ostream &out, const Money &m);
    private:
        long long cents_;
};

Money operator*(long long factor, const Money &m);
Money operator/(long long factor, const Money &m);