#include <vector>
#include <ranges>
#include <iostream>

int main()
{
	std::vector v1 = { 1, 2, 3 };

	std::ranges::ref_view r1 = v1;

	auto p1 = r1.begin();
	auto p2 = r1.end();

	// base() 
	std::cout << &v1        << std::endl;
	std::cout << &r1.base() << std::endl;
}
