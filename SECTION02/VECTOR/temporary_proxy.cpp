#include <iostream>
#include <vector>

int main()
{
	std::vector<int> vi(10);
	std::vector<bool> vb(10);

	auto a1 = vi[0]; // int a1
	auto a2 = vb[0]; // proxy a2

	std::cout << typeid(a1).name() << std::endl;
	std::cout << typeid(a2).name() << std::endl;

	for (auto& e : vi)
		std::cout << e << std::endl;

//	for (auto& e : vb) // error
//	for (const auto& e : vb) // ok
	for (auto&& e : vb) // ok
		std::cout << e << std::endl;
}
