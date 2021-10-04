#include <iostream>

template<typename T> class MyAlloc
{
public:
	// allocate, deallocate ...

	template<typename U> struct rebind
	{
		typedef MyAlloc<U> other;
	};
};

template<typename T> void foo(T ax)
{
	// 현재 T 는 MyAlloc<bool>
	std::cout << typeid(ax).name() << std::endl;

	// MyAlloc<bool> => MyAlloc<int> 로 변경
	typename T::template rebind<int>::other ax2; // MyAlloc<int> ax2

	std::cout << typeid(ax2).name() << std::endl;
}

int main()
{
//	MyAlloc<bool> ax;
	std::allocator<bool> ax;
	foo(ax);
}
