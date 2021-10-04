#include <iostream>
#include "Point.h"

template<typename T, typename Alloc = std::allocator<T> > class Vector
{
	T* buff;
	std::size_t size;
	std::size_t capacity;

	Alloc ax;
public:
	Vector(std::size_t sz, const T& value = T() ) : size(sz), capacity(sz)
	{
		buff = std::allocator_traits<Alloc>::allocate(ax, sizeof(T) * sz);

		int i = 0;
		try
		{
			for( i = 0; i < sz; i++)
				std::allocator_traits<Alloc>::construct(ax, &buff[i], value);
		}
		catch(...)
		{
			for( int j = i-1; j >= 0; --j)
				std::allocator_traits<Alloc>::destroy(ax, &buff[i]);

			std::allocator_traits<Alloc>::deallocate(ax, buff, capacity);
			size = 0;
			capacity = 0;

			throw;
		}
	}

	~Vector()
	{
		for( int j = size-1; j >= 0; --j)
			std::allocator_traits<Alloc>::destroy(ax, &buff[j]);

		std::allocator_traits<Alloc>::deallocate(ax, buff, capacity);
	}
};

// vector<bool> 을 위한 부분 특수화
template<typename Alloc >
class Vector<bool, Alloc>
{
	int* buff;
	std::size_t size;
	std::size_t capacity;

//	Alloc ax; // std::allocator<bool>
//	typename std::allocator_traits<Alloc>::template rebind_alloc<int> ax;

	using Alloc2 = typename std::allocator_traits<Alloc>::template rebind_alloc<int>;

	Alloc2 ax; // std::allocator<int>

public:
	Vector(std::size_t sz, const bool value = false ) : size(sz), capacity(sz)
	{
		// 100bit => 100 / sizeof(int) + 1
		buff = std::allocator_traits<Alloc2>::allocate(ax, sz / sizeof(int) + 1);

		// buff 의 모든 비트를 value 로 초기화.. - 생략..


	}

	~Vector()
	{
		std::allocator_traits<Alloc2>::deallocate(ax, buff, capacity);
	}
};


int main()
{
	Vector<int>  v1(100, 3);
	Vector<bool> v2(100, false);
}
