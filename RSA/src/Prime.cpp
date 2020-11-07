#include "Prime.hpp"
#include <iostream>
#include <fstream>
#include <vector>

std::set<BigInt> Prime::_prime_set = std::set<BigInt>({ 2, 3 });
//std::set<BigInt> Prime::_prime_set = _get_prime_set(1e8);

std::set<BigInt> Prime::_get_prime_set(BigInt limit)
{
    std::set<BigInt> primes = std::set<BigInt>({ 2, 3 });
    std::ifstream ifs(filename);
    std::string str;
    while (ifs >> str)
    {
        if ((limit > 0) && (limit < str))
        {
            std::cout << "Loaded prime numbers up to " << limit << std::endl;
            break;
        }
        primes.emplace_hint(primes.end(), str);
    }
    return primes;
}

bool Prime::use_file = true;

std::string Prime::filename = "../primes/primes.txt";

BigInt Prime::get_biggest_prime()
{
    if (use_file)
    {
        std::ifstream ifs(filename, std::ios::ate);
        std::vector<char> charvec;
        bool start = false;
        char c;
        for (int i = 1; i <= ifs.tellg(); i++)
        {
            ifs.seekg(-i, std::ios::end);
            ifs.get(c);
            if (!start)
            {
                if ((c == ' ') || (c == '\n'))
                    continue;
                else
                    start = true;
            }
            if ((c == ' ') || (c == '\n'))
                break;
            charvec.push_back(c);
        }
        std::string str(charvec.rbegin(), charvec.rend());
        return str;
    }
    else
    {
        return *_prime_set.rbegin();
    }
}

void Prime::print_primes()
{
    std::cout << "Known prime numbers:";
    for (const auto& p : _prime_set)
        std::cout << " " << p;
    std::cout << std::endl;
}

bool Prime::switch_to_memory(const BigInt& num)
{
    if (use_file)
    {
        BigInt biggest_prime = get_biggest_prime();
        if (biggest_prime * biggest_prime < num)
        {
            std::cout << "Maximum prime number in " << filename << " is " << biggest_prime << std::endl;
            std::cout << "We must calculate up to square root of " << num << std::endl;
            std::cout << "Loading all data to memory" << std::endl;
            std::ifstream ifs(filename);
            std::string str;
            while (ifs >> str)
                _prime_set.emplace_hint(_prime_set.end(), str);
            std::cout << "All data is loaded to memory" << std::endl;
            use_file = false;
        }
    }
    return use_file;
}

bool Prime::isprime(BigInt num)
{
    // directly compare with known prime numbers
    if (_prime_set.count(num))
        return true;

    // check whether num is divisible by known prime numbers
    if (use_file)
    {
        std::ifstream ifs(filename);
        std::string str;
        while (ifs >> str)
        {
            BigInt p = str;
            if (num % p == 0)
                return false;
            if (p * p > num)
                return true;
        }
    }
    else
    {
        for (const auto& p : _prime_set)
        {
            if (num % p == 0)
                return false;
            if (p * p > num)
                return true;
        }
    }

    // we must calculate prime numbers up to square root of num
    switch_to_memory(num);

    for (auto i = get_biggest_prime() + 2; i * i <= num; i += 2)
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

std::map<BigInt, int> Prime::factor(BigInt num)
{
    std::map<BigInt, int> fact;

    // find prime factor and add it to the map
    BigInt rem = num;
    while (rem > 1)
    {
        BigInt divisor = -1;
        if (use_file)
        {
            std::ifstream ifs(filename);
            std::string str;
            while (ifs >> str)
            {
                BigInt p = str;
                if (rem % p == 0)
                {
                    divisor = p;
                    break;
                }
                if (p * p > rem)
                {
                    divisor = rem;
                    break;
                }
            }
            switch_to_memory(rem);
        }
        if (!use_file)
        {
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

void Prime::print_factor(BigInt num)
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
