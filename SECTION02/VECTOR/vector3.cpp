#include <iostream>
#include "Point.h"

template <typename T> struct MyAlloc
{
    T* allocate(std::size_t n)
    {
        T* p = static_cast<T*>(std::malloc(n * sizeof(T)));
        std::cout << "allocate" << std::endl;
        return p;
    }
    void deallocate(T* p, std::size_t n) noexcept
    {
        free(p);
        std::cout << "deallocate" << std::endl;
    }
    template<typename ... ARGS> void construct(T* p, ARGS&& ... args)
    {
        new(p) T(std::forward<ARGS>(args)...);
        std::cout << "MyAlloc construct" << std::endl;
    }
    void destroy(T* p)
    {
        p->~T();
        std::cout << "MyAlloc destroy" << std::endl;
    }

	using value_type = T;
};

template<typename T, typename Alloc = std::allocator<T> > class Vector
{
	T* buff;
	std::size_t size;
	std::size_t capacity;

	Alloc ax;
public:
	Vector(std::size_t sz, const T& value = T() ) : size(sz), capacity(sz)
	{
		//buff = static_cast<Point*>(operator new(sizeof(Point) * sz));
		buff = std::allocator_traits<Alloc>::allocate(ax, sizeof(T) * sz);

		int i = 0;
		try
		{
			for( i = 0; i < sz; i++)
			{
				//new(&buff[i]) T(value);
				std::allocator_traits<Alloc>::construct(ax, &buff[i], value);
			}
		}
		catch(...)
		{
			for( int j = i-1; j >= 0; --j)
			//	buff[j].~T();
				std::allocator_traits<Alloc>::destroy(ax, &buff[i]);

			//operator delete(buff);
			std::allocator_traits<Alloc>::deallocate(ax, buff, capacity);
			size = 0;
			capacity = 0;

			throw;
		}
	}

	~Vector()
	{
		for( int j = size-1; j >= 0; --j)
//			buff[j].~T();
			std::allocator_traits<Alloc>::destroy(ax, &buff[j]);

//		operator delete(buff);
		std::allocator_traits<Alloc>::deallocate(ax, buff, capacity);
	}
};
int main()
{
	Point pt(0,0);
//	Vector<Point> v(10, pt);
	Vector<Point, MyAlloc<Point>> v(10, pt);
}
