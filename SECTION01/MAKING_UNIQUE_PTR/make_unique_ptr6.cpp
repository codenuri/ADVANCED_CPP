#include <iostream>
#include <algorithm>
#include "default_delete.h"
#include "compressed_pair.h"

template <typename T, typename D = default_delete<T> > class unique_ptr
{
public:
	using pointer = T*;
	using element_type = T;
	using deleter_type = D;

	unique_ptr() : cpair(zero_and_variadic_args_t{}) {}
	unique_ptr(std::nullptr_t) 			: cpair(zero_and_variadic_args_t{}) {}
	explicit unique_ptr(pointer p) 		: cpair(zero_and_variadic_args_t{}, p) {}
	unique_ptr(pointer p, const D& d) 	: cpair(one_and_variadic_args_t{}, d, p) {}
	unique_ptr(pointer p, D&& d) 		: cpair(one_and_variadic_args_t{}, std::move(d), p) {}

	~unique_ptr() { if (cpair.getSecond()) cpair.getFirst()(cpair.getSecond()); }

	T& operator*()       const { return *cpair.getSecond(); }
	pointer operator->() const { return cpair.getSecond(); }

	// 멤버 함수 추가
	pointer get() const { return cpair.getSecond(); }

	D& get_deleter()  { return cpair.getFirst(); }
	const D& get_deleter() const  { return cpair.getFirst(); }


	explicit operator bool() const { return static_cast<bool>(cpair.getSecond()); }

	pointer release()  { return std::exchange(cpair.getSecond(), nullptr); }

	void reset(pointer ptr = nullptr)
	{
		pointer old = std::exchange(cpair.getSecond(), ptr);
		if (old) {
			cpair.getFirst()(old);
		}
	}

	void swap(unique_ptr& up)
	{
		std::swap(cpair.getFirst(), up.cpair.getFirst());
		std::swap(cpair.getSecond(), up.cpair.getSecond());
	}

private:
	compressed_pair<D, pointer> cpair;
};

int main()
{
	unique_ptr<int> up1(new int);
	unique_ptr<int> up2(new int);

	auto p = up1.get();
	auto d = up1.get_deleter();

	up1.swap(up2);

	if (up1) {}

	p = up1.release();

	up2.reset(new int);
}
