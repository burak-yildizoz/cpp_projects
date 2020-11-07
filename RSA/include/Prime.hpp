#ifndef PRIME_HPP
#define PRIME_HPP

#include <set>
#include <map>
#include <string>
#include "BigInt.hpp"

class Prime
{
    // set of known prime numbers
    static std::set<BigInt> _prime_set;

    // use it to initialize prime numbers from file
    static std::set<BigInt> _get_prime_set(BigInt limit);

public:

    // do not calculate primes, instead read from file
    static bool use_file;

    // path to file of known prime numbers
    static std::string filename;

    // returns biggest known prime dependint on *use_file*
    static BigInt get_biggest_prime();

    // print known prime numbers
    static void print_primes();

    // when the square of biggest known prime number is less than num
    // we must calculate prime numbers up to square root of num
    static bool switch_to_memory(const BigInt& num);

    // check whether a number is a prime number
    static bool isprime(BigInt num);

    // return occurences of prime factors
    // example input: 24
    // output: {{2, 3}, {3, 1}}
    static std::map<BigInt, int> factor(BigInt num);

    // print prime factorization
    // example input: 24
    // output: 24 = 2^3 * 3
    static void print_factor(BigInt num);
};

#endif  // PRIME_HPP
