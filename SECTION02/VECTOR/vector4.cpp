#include <iostream>
#include <vector>

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

	template<typename U> MyAlloc(const MyAlloc<U>&) noexcept {}

	MyAlloc() = default;
};
// == , !=
template<typename T, typename U>
bool operator==(const MyAlloc<T>&, const MyAlloc<U>&) { return true;}
template<typename T, typename U>
bool operator!=(const MyAlloc<T>&, const MyAlloc<U>&) { return false;}



int main()
{
//	std::vector<int> v(10); // std::vector<int, std::allocator<int>>

	std::vector<int, MyAlloc<int> > v(10);

}
