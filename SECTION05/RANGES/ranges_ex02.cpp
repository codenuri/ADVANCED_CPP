#include <vector>
#include <iostream>

template<typename T> class take_view
{
	T& rng;
	std::size_t count;
public:
	take_view(T& r, std::size_t c) : rng(r), count(c) {}

	auto begin() { return rng.begin(); }
	auto end()   { return rng.begin() + count; }
};

int main()
{
	std::vector v = { 1, 2, 3, 4, 5 };

	take_view tv(v, 3);
	for (auto e : tv)
	{
		std::cout << e << std::endl;
	}

	for (auto e : take_view{v, 3} )
	{
		std::cout << e << std::endl;
	}
}
