#include <iostream>
#include <string>
#include <type_traits>

struct one_and_variadic_arg_t  { explicit one_and_variadic_arg_t() = default; };
struct zero_and_variadic_arg_t { explicit zero_and_variadic_arg_t() = default;};

template<typename T1, typename T2, bool = std::is_empty_v<T1> > struct compressed_pair;

template<typename T1, typename T2> struct compressed_pair<T1, T2, false>
{
	T1 first;
	T2 second;

	constexpr T1& getFirst() noexcept  { return first; }
    constexpr T2& getSecond()noexcept { return second; }
	constexpr const T1& getFirst()  const noexcept { return first; }
	constexpr const T2& getSecond() const noexcept { return second; }

    template<typename A1, typename ... A2>
	constexpr compressed_pair( one_and_variadic_arg_t, A1&& arg1, A2&& ... arg2) noexcept(
        std::conjunction_v< std::is_nothrow_constructible<T1, A1>, std::is_nothrow_constructible<T2, A2...> > )
        : first( std::forward<A1>(arg1) ), second( std::forward<A2>(arg2)... ) {}

    template<typename ... A2>
	constexpr compressed_pair( zero_and_variadic_arg_t, A2&& ... arg2) noexcept(
        std::conjunction_v< std::is_nothrow_default_constructible<T1>, std::is_nothrow_constructible<T2, A2...> > )
        : first(), second( std::forward<A2>(arg2)... ) {}
};
int main()
{
	compressed_pair<int, int> cp1( one_and_variadic_arg_t{}, 1, 1);
}