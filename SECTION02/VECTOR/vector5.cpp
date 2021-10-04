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
	T* buff;
	std::size_t size;
	std::size_t capacity;

	Alloc ax;
public:
	Vector(std::size_t sz, const T& value = T() ) : size(sz), capacity(sz)
	{
	//	buff = std::allocator_traits<Alloc>::allocate(ax, sizeof(T) * sz);

		// sz bit 만큼 할당.. new int[sz/sizeof(int)]
		// ax => std::allocator<bool> ===> std::allocator<int> 로 변경이 필요 하다.

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


int main()
{
	Vector<int>  v1(100, 3);
	Vector<bool> v2(100, false);
}
