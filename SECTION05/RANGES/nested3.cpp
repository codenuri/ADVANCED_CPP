#include <vector>
#include <iostream>
#include <ranges>
#include <concepts>

template<typename T> class take_view : public std::ranges::view_base
{
	std::ranges::ref_view<T> rng;
	std::size_t count;
public:
	take_view() = default;
	take_view(T& r, std::size_t c) : rng(r), count(c) {}
	auto begin() { return rng.begin(); }
	auto end()   { return rng.begin() + count; }
};

template<typename T> auto all(T&& arg)
{
	if constexpr ( std::ranges::view<std::remove_cvref_t<T>> )
	{
		std::cout << "view" << std::endl;

		// 복사본 반환
		return std::remove_cvref_t<T>(arg);
	}
	else
	{
		std::cout << "not view" << std::endl;
		// vector => ref_view<vector>
		return std::ranges::ref_view<std::remove_cvref_t<T>> (arg);
	}
}

int main()
{
	std::vector v = { 1, 2, 3 };
	take_view tv(v, 2);

	auto a1 = all(v);
	auto a2 = all(tv);

	std::cout << typeid(a1).name() << std::endl;
	std::cout << typeid(a2).name() << std::endl;
}
