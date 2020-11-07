#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>

struct BigInt
{
    int sign;
    std::string s;

    BigInt();
    BigInt(std::string x);
    BigInt(int x);

    BigInt negative();
    BigInt normalize(int newSign);

    void operator=(std::string x);
    bool operator==(const BigInt& x) const;
    bool operator!=(const BigInt& x) const;
    bool operator<(const BigInt& x) const;
    bool operator<=(const BigInt& x) const;
    bool operator>(const BigInt& x) const;
    bool operator>=(const BigInt& x) const;
    BigInt operator+(BigInt x) const;
    BigInt operator-(BigInt x) const;
    BigInt operator*(BigInt x) const;
    BigInt operator/(BigInt x) const;
    BigInt operator%(BigInt x) const;
    BigInt& operator+=(BigInt x);
    BigInt& operator-=(BigInt x);
    BigInt& operator*=(BigInt x);
    BigInt& operator/=(BigInt x);
    BigInt& operator%=(BigInt x);
    BigInt& operator++();
    BigInt& operator--();
    BigInt& operator++(int);
    BigInt& operator--(int);

    std::string toString() const;

    BigInt toBase10(int base);
    BigInt toBase10(int base, BigInt mod);

    std::string convertToBase(int base);

    BigInt toBase(int base);

    friend std::ostream& operator<<(std::ostream& os, const BigInt& x);
};

#endif  // BIGINT_HPP
