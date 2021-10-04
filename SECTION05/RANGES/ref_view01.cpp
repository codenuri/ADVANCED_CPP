#include <vector>
#include <ranges>
#include <iostream>

int main()
{
	std::vector v1 = { 1, 2, 3 };
	std::vector v2 = { 5, 6, 7, 8, 9 };

	std::vector<int>& r1 = v1;
	std::vector<int>& r2 = v2;

	r1 = r2; // 이 코드의 실행 결과는 ?

	std::cout << v1.size() << std::endl; // 5
	std::cout << v2.size() << std::endl; // 5
	std::cout << r1.size() << std::endl; // 5
	std::cout << r2.size() << std::endl; // 5
}
