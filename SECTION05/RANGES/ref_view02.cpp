#include <vector>
#include <ranges>
#include <iostream>

int main()
{
	std::vector v1 = { 1, 2, 3 };
	std::vector v2 = { 5, 6, 7, 8, 9 };

//	std::vector<int>& r1 = v1;
//	std::vector<int>& r2 = v2;

	std::ranges::ref_view r1 = v1;
	std::ranges::ref_view r2 = v2;

	r1 = r2;

	std::cout << v1.size() << std::endl; // 3
	std::cout << v2.size() << std::endl; // 5
	std::cout << r1.size() << std::endl; // 5
	std::cout << r2.size() << std::endl; // 5
}
