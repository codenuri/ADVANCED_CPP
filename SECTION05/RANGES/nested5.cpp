#include <vector>
#include <iostream>
#include <ranges>

template<typename T> class take_view : public std::ranges::view_base
{
	T rng;
	std::size_t count;
public:
	take_view() = default;

	take_view(T r, std::size_t c) : rng(r), count(c) {}
	auto begin() { return rng.begin(); }
	auto end()   { return rng.begin() + count; }
};
template<typename T>
take_view(T&& t, std::size_t)->take_view< std::views::all_t<T> >;


template<typename T> class reverse_view : public std::ranges::view_base
{
	T rng;
public:
	reverse_view() = default;
	reverse_view(T& r) : rng(r) {}

	auto begin() { return std::make_reverse_iterator(rng.end()); }
	auto end() { return std::make_reverse_iterator(rng.begin()); }
};
template<typename T>
reverse_view(T&&)->reverse_view<std::views::all_t<T>>;


int main()
{
	std::vector v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	reverse_view rv(v);
	take_view tv(rv, 3);

	for( auto e : tv) // 10, 9, 8
		std::cout << e << std::endl;

	for( auto e : take_view( reverse_view(v), 3) )
		std::cout << e << std::endl;

}
