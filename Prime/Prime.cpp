#include <iostream>

#include "Prime.hpp"

std::set<long long> Prime::_prime_set = std::set<long long>({2, 3});

void Prime::print_primes()
{
    std::cout << "Known prime numbers:";
    for (const auto& p : _prime_set)
        std::cout << " " << p;
    std::cout << std::endl;
}

bool Prime::isprime(size_t num)
{
    // biggest known prime number
    auto biggest_prime = *_prime_set.rbegin();
    if ((size_t)biggest_prime > num)
    {
        if (_prime_set.count(num))
            return true;
        else
            return false;
    }

    // check whether num is divisible by known prime numbers
    for (const auto& p : _prime_set)
    {
        if (num % p == 0)
            return false;
        if ((double)p * p > num)
            break;
    }

    // if num is less than biggest_prime squared, then it is a prime number
    // in this case, simply return true instead of calculating prime numbers
    if ((double)biggest_prime * biggest_prime > num)
        return true;

    // we must calculate prime numbers up to square root of num
    for (auto i = biggest_prime + 2; (double)i * i <= num; i += 2)
    {
        if (isprime(i))
        {
            _prime_set.emplace_hint(_prime_set.end(), i);
            if (num % i == 0)
                return false;
        }
    }

    return true;
}

std::map<long long, int> Prime::factor(long long num)
{
    std::map<long long, int> fact;

    // find prime factor and add it to the map
    long long rem = num;
    while (rem > 1)
    {
        long long divisor = -1;
        // calculate necessary prime numbers
        if (isprime(rem))
        {
            divisor = rem;
        }
        else
        {
            // check if any known prime number divides rem
            for (const auto& p : _prime_set)
            {
                if (rem % p == 0)
                {
                    divisor = p;
                    break;
                }
            }
        }

        // add divisor to the map
        auto it = fact.find(divisor);
        if (it == fact.end())
            fact.emplace_hint(fact.end(), divisor, 1);
        else
            it->second++;
        // calculate prime factorization of the remaining part
        rem /= divisor;
    }

    return fact;
}

void Prime::print_factor(long long num)
{
    std::cout << num << " =";
    auto fact = factor(num);
    for (auto cit = fact.cbegin(); cit != fact.cend(); ++cit)
    {
        auto& p = *cit;
        if (cit != fact.cbegin())
            std::cout << " *";
        std::cout << " " << p.first;
        if (p.second > 1)
            std::cout << "^" << p.second;
    }
    std::cout << std::endl;
}
