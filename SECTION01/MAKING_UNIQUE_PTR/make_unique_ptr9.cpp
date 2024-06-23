#include <iostream>
#include <algorithm>
#include <utility>
#include "default_delete.h"
#include "compressed_pair.h"


template <typename T, typename D = default_delete<T> > class unique_ptr
{
				// T : int[]
public:
	using pointer = T*;		// int[]*
	using element_type = T;
	using deleter_type = D;

	unique_ptr() noexcept: cpair(zero_and_variadic_args_t{}) {}
	unique_ptr(std::nullptr_t)     noexcept	: cpair(zero_and_variadic_args_t{}) {}
	explicit unique_ptr(pointer p) noexcept	: cpair(zero_and_variadic_args_t{}, p) {}
	unique_ptr(pointer p, const D& d) noexcept	: cpair(one_and_variadic_args_t{}, d, p) {}
	unique_ptr(pointer p, D&& d) 	noexcept	: cpair(one_and_variadic_args_t{}, std::move(d), p) {}

	~unique_ptr() noexcept{ if (cpair.getSecond()) cpair.getFirst()(cpair.getSecond()); }

	T& operator*()       const noexcept { return *cpair.getSecond(); }
	pointer operator->() const noexcept { return cpair.getSecond(); }

	// 멤버 함수 추가
	pointer get() const noexcept{ return cpair.getSecond(); }

	D& get_deleter()  noexcept { return cpair.getFirst(); }
	const D& get_deleter() const   noexcept { return cpair.getFirst(); }
	explicit operator bool() const noexcept{ return static_cast<bool>(cpair.getSecond()); }
	pointer release()  noexcept { return std::exchange(cpair.getSecond(), nullptr); }
	void reset(pointer ptr = nullptr) noexcept
	{
		pointer old = std::exchange(cpair.getSecond(), ptr);
		if (old) {
			cpair.getFirst()(old);
		}
	}

	void swap(unique_ptr& up) noexcept
	{
		std::swap(cpair.getFirst(),  up.cpair.getFirst());
		std::swap(cpair.getSecond(), up.cpair.getSecond());
	}

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;


	// move constructor
    unique_ptr(unique_ptr&& up) noexcept
        : cpair(one_and_variadic_args_t{}, std::forward<D>(up.get_deleter()), up.release()) {}

    unique_ptr& operator=(unique_ptr&& up) noexcept
    {
        if (this != std::addressof(up))
        {
            reset(up.release());
            cpair.getFirst() = std::forward<D>(up.cpair.getFirst());
        }
        return *this;
    }

	template<typename T2, typename D2>
	unique_ptr(unique_ptr<T2, D2>&& up) noexcept
        : cpair(one_and_variadic_args_t{}, std::forward<D2>(up.get_deleter()), up.release()) {}

	template<typename T2, typename D2>
    unique_ptr& operator=(unique_ptr<T2, D2>&& up) noexcept
    {
        if (this != std::addressof(up))
        {
            reset(up.release());
            cpair.getFirst() = std::forward<D2>(up.cpair.getFirst());
        }
        return *this;
    }

private:
	compressed_pair<D, pointer> cpair;
};

template <typename T, typename D >
class unique_ptr<T[], D>
{
				// T : int
public:
	using pointer = T*;		// int*
	using element_type = T;
	using deleter_type = D;

	unique_ptr() noexcept: cpair(zero_and_variadic_args_t{}) {}
	unique_ptr(std::nullptr_t)     noexcept	: cpair(zero_and_variadic_args_t{}) {}
	explicit unique_ptr(pointer p) noexcept	: cpair(zero_and_variadic_args_t{}, p) {}
	unique_ptr(pointer p, const D& d) noexcept	: cpair(one_and_variadic_args_t{}, d, p) {}
	unique_ptr(pointer p, D&& d) 	noexcept	: cpair(one_and_variadic_args_t{}, std::move(d), p) {}

	~unique_ptr() noexcept{ if (cpair.getSecond()) cpair.getFirst()(cpair.getSecond()); }

	T& operator*()       const noexcept { return *cpair.getSecond(); }
	pointer operator->() const noexcept { return cpair.getSecond(); }

	// 멤버 함수 추가
	pointer get() const noexcept{ return cpair.getSecond(); }

	D& get_deleter()  noexcept { return cpair.getFirst(); }
	const D& get_deleter() const   noexcept { return cpair.getFirst(); }
	explicit operator bool() const noexcept{ return static_cast<bool>(cpair.getSecond()); }
	pointer release()  noexcept { return std::exchange(cpair.getSecond(), nullptr); }
	void reset(pointer ptr = nullptr) noexcept
	{
		pointer old = std::exchange(cpair.getSecond(), ptr);
		if (old) {
			cpair.getFirst()(old);
		}
	}

	void swap(unique_ptr& up) noexcept
	{
		std::swap(cpair.getFirst(),  up.cpair.getFirst());
		std::swap(cpair.getSecond(), up.cpair.getSecond());
	}

    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;


	// move constructor
    unique_ptr(unique_ptr&& up) noexcept
        : cpair(one_and_variadic_args_t{}, std::forward<D>(up.get_deleter()), up.release()) {}

    unique_ptr& operator=(unique_ptr&& up) noexcept
    {
        if (this != std::addressof(up))
        {
            reset(up.release());
            cpair.getFirst() = std::forward<D>(up.cpair.getFirst());
        }
        return *this;
    }

	template<typename T2, typename D2>
	unique_ptr(unique_ptr<T2, D2>&& up) noexcept
        : cpair(one_and_variadic_args_t{}, std::forward<D2>(up.get_deleter()), up.release()) {}

	template<typename T2, typename D2>
    unique_ptr& operator=(unique_ptr<T2, D2>&& up) noexcept
    {
        if (this != std::addressof(up))
        {
            reset(up.release());
            cpair.getFirst() = std::forward<D2>(up.cpair.getFirst());
        }
        return *this;
    }

private:
	compressed_pair<D, pointer> cpair;
};


int main()
{
	unique_ptr<int> up1(new int);       // delete
	unique_ptr<int[]> up2(new int[10]); // delete[]
}
