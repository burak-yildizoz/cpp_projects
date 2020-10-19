#include <iostream>
#include "Average.hpp"

int main()
{
	Average<double> avgc(3);
	const double& avg = avgc.ortalama;
	std::cout << avg << std::endl;	// 0
	avgc.add(1);
	std::cout << avg << std::endl;	// 1
	avgc.add(2);
	std::cout << avg << std::endl;	// 1.5
	avgc.add(3);
	std::cout << avg << std::endl;	// 2
	avgc.add(4);
	std::cout << avg << std::endl;	// 3
}
