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

	T& operator[](int idx) { return buff[idx];}
};

// vector<bool> 을 위한 부분 특수화
template<typename Alloc > class Vector<bool, Alloc>
{
	int* buff;
	std::size_t size;
	std::size_t capacity;

	using Alloc2 = typename std::allocator_traits<Alloc>::template rebind_alloc<int>;
	Alloc2 ax;
public:
	Vector(std::size_t sz, const bool value = false ) : size(sz), capacity(sz)
	{
		buff = std::allocator_traits<Alloc2>::allocate(ax, sz / sizeof(int) + 1);
	}
	~Vector()
	{
		std::allocator_traits<Alloc2>::deallocate(ax, buff, capacity);
	}

	struct BitProxy
	{
		int* buff;
		int idx;

		BitProxy(int* buff, int idx) : buff(buff), idx(idx) {}

		BitProxy& operator=(bool value)
		{
			printf("addr : %p  idx : %d  value : %d\n", buff, idx, value);

			return *this;
		}
		// bool 로의 변환을 위한 변환 연산자.
		operator bool()
		{
			printf("get addr : %p idx : %d\n", buff, idx);
			return true;
		}
	};
	// 현재 코드는 "비트" 단위로 관리..
	// 비트 단위로 반환해야 한다.
	BitProxy operator[](int idx) { return BitProxy(buff, idx);}
};

int main()
{
	Vector<bool> v2(100, false);

	v2[0] = true; // v2.buff 주소의 0 번째 비트에 접근
				  // BitProxy객체.operator=(true)
	bool b = v2[0]; // BitProxy객체.operator bool()
}
