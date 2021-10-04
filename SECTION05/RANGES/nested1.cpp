#include <vector>
#include <iostream>
#include <ranges>

template<typename T> class take_view
{
	std::ranges::ref_view<T> rng;
	std::size_t count;
public:
	take_view(T& r, std::size_t c)
						: rng(r), count(c) {}
	auto begin() { return rng.begin(); }
	auto end()   { return rng.begin() + count; }
};

template<typename T> class reverse_view
{
	std::ranges::ref_view<T> rng;
public:
	reverse_view(T& r) : rng(r){}

	auto begin() { return std::make_reverse_iterator(rng.end()); }
	auto end() { return std::make_reverse_iterator(rng.begin()); }
};

int main()
{
	std::vector v = { 1, 2, 3 };

	for ( auto e : reverse_view(v) )
		std::cout << e << std::endl;

	std::ranges::ref_view r1(v);
//	std::ranges::ref_view r2( std::vector<int>{1,2,3} ); // error.
}
