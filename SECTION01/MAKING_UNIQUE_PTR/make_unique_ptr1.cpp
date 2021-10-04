#include <iostream>
#include "Car.h"

template <typename T> class unique_ptr 
{ 
    T* pobj;
public:
    explicit unique_ptr(T* p) : pobj(p) {}

    ~unique_ptr()
    {
        if ( pobj )
            delete pobj;
    }

	T& operator*()  const { return *pobj; }
    T* operator->() const { return pobj; }
};
int main()
{
//	unique_ptr<Car> p1 = new Car; 	// error
    const unique_ptr<Car> p2(new Car); 	// ok
    
    p2->Go();
    (*p2).Go();
}

