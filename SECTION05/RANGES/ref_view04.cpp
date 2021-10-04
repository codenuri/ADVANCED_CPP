#include <vector>
#include <iostream>
#include <ranges>

template<typename T> class take_view
{
	T& rng;
	std::size_t count;
public:
	take_view(T& r, std::size_t c)
						: rng(r), count(c) {}
	auto begin() { return rng.begin(); }
	auto end()   { return rng.begin() + count; }

	take_view& operator=(const take_view& tv)
	{
		if (&tv == this) return *this;

		rng = tv.rng;
		count = tv.count;

		return *this;
	}

};
int main()
{
	std::vector v1 = { 1, 2, 3 };
	std::vector v2 = { 5, 6, 7, 8, 9 };

	take_view tv1(v1, 2);
	take_view tv2(v2, 3);

	tv1 = tv2;

	std::cout << v1.size() << std::endl; // 5
	std::cout << v2.size() << std::endl; // 5
}
