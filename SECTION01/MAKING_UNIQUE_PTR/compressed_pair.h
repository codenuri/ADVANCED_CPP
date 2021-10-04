#pragma once
#include <iostream>
#include <type_traits>

struct zero_and_variadic_args_t { explicit zero_and_variadic_args_t() = default; };
struct one_and_variadic_args_t { explicit one_and_variadic_args_t() = default; };

template<typename T1, typename T2, bool = std::is_empty_v<T1> && !std::is_final_v<T1> > struct compressed_pair;

template<typename T1, typename T2> struct compressed_pair<T1, T2, false>
{
	T1 first;
	T2 second;

	constexpr       T1& getFirst() { return first; }
	constexpr const T1& getFirst() const { return first; }

	constexpr T2& getSecond() { return first; }
	constexpr const T2& getSecond() const { return first; }

	template<typename A1, typename ... A2>
	constexpr compressed_pair(one_and_variadic_args_t, A1&& a1, A2&& ... a2) noexcept(
		std::conjunction_v< std::is_nothrow_constructible<T1, A1>, std::is_nothrow_constructible<T2, A2...> >)
		: first(std::forward<A1>(a1)), second(std::forward<A2>(a2)...)
	{}

	template<typename ... A2>
	constexpr explicit compressed_pair(zero_and_variadic_args_t, A2&& ... a2) noexcept(
		std::conjunction_v< std::is_nothrow_default_constructible<T1>, std::is_nothrow_constructible<T2, A2...> >)
		: first(), second(std::forward<A2>(a2)...)
	{}
};

template<typename T1, typename T2> struct compressed_pair<T1, T2, true> : private T1
{
	T2 second;

	constexpr       T1& getFirst() noexcept { return *this; }
	constexpr const T1& getFirst() const noexcept { return *this; }

	constexpr T2& getSecond() noexcept { return second; }
	constexpr const T2& getSecond() const noexcept { return second; }

	template<typename A1, typename ... A2>
	constexpr compressed_pair(one_and_variadic_args_t, A1&& a1, A2&& ... a2) noexcept(
		std::conjunction_v< std::is_nothrow_constructible<T1, A1>, std::is_nothrow_constructible<T2, A2...> >)
		: T1(std::forward<A1>(a1)), second(std::forward<A2>(a2)...)
	{}

	template<typename ... A2>
	constexpr explicit compressed_pair(zero_and_variadic_args_t, A2&& ... a2) noexcept(
		std::conjunction_v< std::is_nothrow_default_constructible<T1>, std::is_nothrow_constructible<T2, A2...> >)
		: T1(), second(std::forward<A2>(a2)...)
	{}
};