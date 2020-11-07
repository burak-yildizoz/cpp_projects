#include "BigInt.hpp"
#include <algorithm>

BigInt::BigInt()
    : s("")
{
}

BigInt::BigInt(std::string x)
{
    *this = x;
}

BigInt::BigInt(int x)
{
    *this = std::to_string(x);
}

BigInt BigInt::negative()
{
    BigInt x = *this;

    x.sign *= -1;

    return x;
}

BigInt BigInt::normalize(int newSign)
{
    for (int a = s.size() - 1; a > 0 && s[a] == '0'; a--)
        s.erase(s.begin() + a);

    sign = (s.size() == 1 && s[0] == '0' ? 1 : newSign);

    return *this;
}

void BigInt::operator=(std::string x)
{
    int newSign = (x[0] == '-' ? -1 : 1);

    s = (newSign == -1 ? x.substr(1) : x);

    std::reverse(s.begin(), s.end());

    this->normalize(newSign);
}

bool BigInt::operator==(const BigInt& x) const
{
    return (s == x.s && sign == x.sign);
}

bool BigInt::operator!=(const BigInt& x) const
{
    return (s != x.s || sign != x.sign);
}

bool BigInt::operator<(const BigInt& x) const
{
    if (sign != x.sign)
        return sign < x.sign;

    if (s.size() != x.s.size())
        return (sign == 1 ? s.size() < x.s.size() : s.size() > x.s.size());

    for (int a = s.size() - 1; a >= 0; a--)
        if (s[a] != x.s[a])
            return (sign == 1 ? s[a] < x.s[a] : s[a] > x.s[a]);

    return false;
}

bool BigInt::operator<=(const BigInt& x) const
{
    return (*this == x || *this < x);
}

bool BigInt::operator>(const BigInt& x) const
{
    return (!(*this == x) && !(*this < x));
}

bool BigInt::operator>=(const BigInt& x) const
{
    return (*this == x || *this > x);
}

BigInt BigInt::operator+(BigInt x) const
{
    BigInt curr = *this;

    if (curr.sign != x.sign)
        return curr - x.negative();

    BigInt res;

    for (int a = 0, carry = 0; a < (int)s.size() || a < (int)x.s.size() || carry; a++) {
        carry += (a < (int)curr.s.size() ? curr.s[a] - '0' : 0) + (a < (int)x.s.size() ? x.s[a] - '0' : 0);

        res.s += (carry % 10 + '0');

        carry /= 10;
    }

    return res.normalize(sign);
}

BigInt BigInt::operator-(BigInt x) const
{
    BigInt curr = *this;

    if (curr.sign != x.sign)
        return curr + x.negative();

    int realSign = curr.sign;

    curr.sign = x.sign = 1;

    if (curr < x)
        return ((x - curr).negative()).normalize(-realSign);

    BigInt res;

    for (int a = 0, borrow = 0; a < (int)s.size(); a++) {
        borrow = (curr.s[a] - borrow - (a < (int)x.s.size() ? x.s[a] : '0'));

        res.s += (borrow >= 0 ? borrow + '0' : borrow + '0' + 10);

        borrow = (borrow >= 0 ? 0 : 1);
    }

    return res.normalize(realSign);
}

BigInt BigInt::operator*(BigInt x) const
{
    BigInt res("0");

    for (int a = 0, b = s[a] - '0'; a < (int)s.size(); a++, b = s[a] - '0') {
        while (b--)
            res = (res + x);

        x.s.insert(x.s.begin(), '0');
    }

    return res.normalize(sign * x.sign);
}

BigInt BigInt::operator/(BigInt x) const
{
    if (x.s.size() == 1 && x.s[0] == '0')
        x.s[0] /= (x.s[0] - '0');

    BigInt temp("0"), res;

    for (int a = 0; a < (int)s.size(); a++)
        res.s += "0";

    int newSign = sign * x.sign;

    x.sign = 1;

    for (int a = s.size() - 1; a >= 0; a--) {
        temp.s.insert(temp.s.begin(), '0');
        temp = temp + s.substr(a, 1);

        while (!(temp < x)) {
            temp = temp - x;
            res.s[a]++;
        }
    }

    return res.normalize(newSign);
}

BigInt BigInt::operator%(BigInt x) const
{
    if (x.s.size() == 1 && x.s[0] == '0')
        x.s[0] /= (x.s[0] - '0');

    BigInt res("0");

    x.sign = 1;

    for (int a = s.size() - 1; a >= 0; a--) {
        res.s.insert(res.s.begin(), '0');

        res = res + s.substr(a, 1);

        while (!(res < x))
            res = res - x;
    }

    return res.normalize(sign);
}

BigInt& BigInt::operator+=(BigInt x)
{
    *this = *this + x;
    return *this;
}

BigInt& BigInt::operator-=(BigInt x)
{
    *this = *this - x;
    return *this;
}

BigInt& BigInt::operator*=(BigInt x)
{
    *this = *this * x;
    return *this;
}

BigInt& BigInt::operator/=(BigInt x)
{
    *this = *this / x;
    return *this;
}

BigInt& BigInt::operator%=(BigInt x)
{
    *this = *this % x;
    return *this;
}

BigInt& BigInt::operator++()
{
    *this += 1;
    return *this;
}

BigInt& BigInt::operator--()
{
    *this -= 1;
    return *this;
}

BigInt& BigInt::operator++(int)
{
    *this += 1;
    return *this;
}

BigInt& BigInt::operator--(int)
{
    *this -= 1;
    return *this;
}

std::string BigInt::toString() const
{
    std::string ret = s;

    std::reverse(ret.begin(), ret.end());

    return (sign == -1 ? "-" : "") + ret;
}

BigInt BigInt::toBase10(int base)
{
    BigInt exp(1), res("0"), BASE(base);

    for (int a = 0; a < (int)s.size(); a++) {
        int curr = (s[a] < '0' || s[a] > '9' ? (toupper(s[a]) - 'A' + 10) : (s[a] - '0'));

        res = res + (exp * BigInt(curr));
        exp = exp * BASE;
    }

    return res.normalize(sign);
}

BigInt BigInt::toBase10(int base, BigInt mod)
{
    BigInt exp(1), res("0"), BASE(base);

    for (int a = 0; a < (int)s.size(); a++) {
        int curr = (s[a] < '0' || s[a] > '9' ? (toupper(s[a]) - 'A' + 10) : (s[a] - '0'));

        res = (res + ((exp * BigInt(curr) % mod)) % mod);
        exp = ((exp * BASE) % mod);
    }

    return res.normalize(sign);
}

std::string BigInt::convertToBase(int base)
{
    BigInt ZERO(0), BASE(base), x = *this;
    std::string modes = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    if (x == ZERO)
        return "0";

    std::string res = "";

    while (x > ZERO) {
        BigInt mod = x % BASE;

        x = x - mod;

        if (x > ZERO)
            x = x / BASE;

        res = modes[stoi(mod.toString())] + res;
    }

    return res;
}

BigInt BigInt::toBase(int base)
{
    return BigInt(this->convertToBase(base));
}

std::ostream& operator<<(std::ostream& os, const BigInt& x)
{
    os << x.toString();

    return os;
}
