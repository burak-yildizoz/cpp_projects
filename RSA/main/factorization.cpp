#include <string>

#include "Prime.hpp"

int main(int argc, char** argv)
{
    if (argc > 1)
      Prime::filename = argv[1];

    while (true)
    {
        std::cout << "Enter a number to see its prime factorization: ";

        std::string num_str;
        std::cin >> num_str;

        Prime::print_factor(num_str);
    }

    return 0;
}
