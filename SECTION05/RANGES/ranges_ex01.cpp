#include <vector>
#include <iostream>

int main()
{
	std::vector v = { 1, 2, 3, 4, 5 };

	for (auto e : v)
	{
		std::cout << e << std::endl;
	}
}
