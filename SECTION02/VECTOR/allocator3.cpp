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

/*
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
*/
	using value_type = T;
};
int main()
{
	MyAlloc<Point> ax;

//	Point* p1 = ax.allocate(1);

//	ax.construct(p1, 0, 0);
//	ax.destroy(p1);

	Point* p1 =std::allocator_traits<MyAlloc<Point>>::allocate(ax, 1);
	std::allocator_traits<MyAlloc<Point>>::construct( ax, p1, 0, 0  );
	std::allocator_traits<MyAlloc<Point>>::destroy(ax, p1);
	std::allocator_traits<MyAlloc<Point>>::deallocate(ax, p1, 1);

//	ax.deallocate(p1, 1);
}
