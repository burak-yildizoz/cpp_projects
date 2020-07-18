#include <string>
#include <cstdlib>

#include "Prime.hpp"

int main()
{
    Prime prime;
    while (true)
    {
        std::cout << "Enter a number to see its prime factorization: ";

        std::string num_str;
        std::cin >> num_str;
        long long num = atoll(num_str.c_str());

        prime.print_factor(num);
    }

    return 0;
}
