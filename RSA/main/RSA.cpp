#include "BigInt.hpp"
#include "Prime.hpp"
#include <string>
#include <cstdlib>
#include <ctime>

BigInt random(int sz)
{
    std::string str(sz, '0');
    for (int i=0; i<sz; i++)
        str[i] += rand()%10;
    return BigInt(str);
}

BigInt random_prime(int sz)
{
    BigInt res;
    do
    {
        res = random(sz);
    } while (!Prime::isprime(res));
    return res;
}

BigInt random(const BigInt& fi)
{
    int sz = 0;
    BigInt temp = fi;
    while (temp > 1)
    {
        temp /= 10;
        sz++;
    }
    return random(sz);
}

BigInt calculate_d(const BigInt& fi, BigInt &e)
{
    for (BigInt dummy = 2; dummy < fi; dummy++)
    {
        e = random(fi);
        BigInt a = e, b = fi, x = 0, y = 1, q;
        while (a > 1 || b > 1)
        {
            if (a == 1)
                return y;
            if (a == 0)
                break;
            q = b / a;
            b -= a * q;
            x += y * q;
            if (b == 1)
                return fi - x;
            if (b == 0)
                break;
            q = a / b;
            a -= b * q;
            y += x * q;
        }
    }
    return -1;
}

#include <iostream>
#define DEBUG(cc) std::cout << #cc << " = " << (cc) << std::endl

int main(int argc, char** argv)
{
    int len = (argc > 1) ? atoi(argv[1]) : 12;
    DEBUG(2*len*10/3);
    if (argc > 2)
      Prime::filename = argv[2];

    BigInt biggest_prime = Prime::get_biggest_prime();
    DEBUG(biggest_prime);
    DEBUG(biggest_prime * biggest_prime);

    srand(time(NULL));
    BigInt p = random_prime(len);
    DEBUG(p);
    BigInt q;
    do
    {
        q=random_prime(len);
    } while(p == q);
    DEBUG(q);
    BigInt n = p*q;
    DEBUG(n);
    BigInt fi = (p - 1) * (q - 1);
    DEBUG(fi);
    BigInt e;
    BigInt d = calculate_d(fi, e);
    DEBUG(e);
    DEBUG(d);
    Prime::print_factor(n);

    return 0;
}
