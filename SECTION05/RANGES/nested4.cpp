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
//take_view(T&& t, std::size_t)->take_view<std::remove_cvref_t<decltype( std::views::all(t) ) > >;
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
	std::vector v = { 1, 2, 3 };

	reverse_view rv(v);

	take_view tv1(v, 2);  // 멤버로 ref_view<vector>
	take_view tv2(rv, 2); // 멤버로 ref_view<reverse_view> 가 아니라 reverse_view 복사본 포함.

	std::cout << typeid(tv1).name() << std::endl;
	std::cout << typeid(tv2).name() << std::endl;
}
