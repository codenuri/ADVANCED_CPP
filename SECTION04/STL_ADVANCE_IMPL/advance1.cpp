#include <iostream>
#include <vector>
#include <list>
#include <iterator>

int main()
{
//	std::vector<int> c = {1,2,3,4,5,6,7,8,9,10};
	std::list<int>   c = {1,2,3,4,5,6,7,8,9,10};

	auto p = std::begin(c);

	// 반복자 p 를 5칸 전진하고 싶다.
//	p = p + 5;
//	++p; ++p; ++p; ++p; ++p;

	std::advance(p, 5);

	std::cout << *p << std::endl;
}
