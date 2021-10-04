#include <iostream>

template<typename T> class MyAlloc
{
public:
	/*
	template<typename U> struct rebind
	{
		typedef MyAlloc<U> other;
	};
	*/
	using value_type = T;
};
template<typename T> void foo(T ax)
{
	// MyAlloc<bool> => MyAlloc<int> 로 변경
	typename T::template rebind<int>::other ax1; // C++98 스타일
	std::cout << typeid(ax1).name() << std::endl;

	typename std::allocator_traits<T>::template rebind_alloc<int> ax2; // C++11 이후..
	std::cout << typeid(ax2).name() << std::endl;  //
}

int main()
{
//	MyAlloc<bool> ax;
	std::allocator<bool> ax;
	foo(ax);
}
