#include <iostream>
#include "Car.h"
#include "default_delete.h"
#include "compressed_pair.h"

template <typename T, typename D = default_delete<T> > 
class unique_ptr 
{ 
//  T* pobj;
//	D del;
	compressed_pair<D, T*> cpair;
public:
    explicit unique_ptr(T* p) : cpair(zero_and_variadic_args_t{}, p) {}
	unique_ptr(T* p, const D& d) : cpair(one_and_variadic_args_t{}, d, p) {}
	unique_ptr(T* p, D&& d)      : cpair(one_and_variadic_args_t{}, std::move(d), p) {}

    ~unique_ptr()
    {
        if ( cpair.getSecond() )
		{
			cpair.getFirst()( cpair.getSecond() );
		}
    }
	T& operator*()  const { return *cpair.getSecond(); }
    T* operator->() const { return cpair.getSecond(); }
};
int main()
{	
	unique_ptr<int> p1(new int);

	auto del = [](int* p) { free(p); };
	unique_ptr<int, decltype(del) > p2(static_cast<int*>(malloc(sizeof(int))), del );

	std::cout << sizeof(p1) << std::endl;
	std::cout << sizeof(p2) << std::endl;
}

