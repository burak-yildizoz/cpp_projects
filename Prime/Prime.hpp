#ifndef PRIME_HPP
#define PRIME_HPP

#include <set>
#include <map>

class Prime
{
    // set of known prime numbers
    static std::set<long long> _prime_set;

public:

    // print known prime numbers
    static void print_primes();

    // check whether a number is a prime number
    bool isprime(size_t num);

    // return occurences of prime factors
    // example input: 24
    // output: {{2, 3}, {3, 1}}
    std::map<long long, int> factor(long long num);

    // print prime factorization
    // example input: 24
    // output: 24 = 2^3 * 3
    void print_factor(long long num);

};

#endif  // PRIME_HPP
