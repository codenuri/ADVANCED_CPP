#include <vector>
#include <iostream>
#include <ranges>

template<typename T> class take_view : public std::ranges::view_interface<take_view<T>>
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

int main()
{
	std::vector v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	take_view tv(v, 3);

	std::cout << tv.size() << std::endl;
	std::cout << tv.empty() << std::endl;
	std::cout << tv.data() << std::endl;

}
