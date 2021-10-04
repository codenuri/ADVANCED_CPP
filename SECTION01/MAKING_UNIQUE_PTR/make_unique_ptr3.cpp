#include <iostream>
#include "Car.h"

template<typename T> struct default_delete
{
	void operator()(T* p) const 
    {
        std::cout << "delete" << std::endl;
        delete p;
    }
};

template <typename T, typename D = default_delete<T> > 
class unique_ptr 
{ 
    T* pobj;
	D del;
public:
    explicit unique_ptr(T* p) : pobj(p) {}

	unique_ptr(T* p, const D& d) : pobj(p), del(d) {} // 삭제자의 복사 생성.
	unique_ptr(T* p, D&& d)      : pobj(p), del(std::move(d)) {}

    ~unique_ptr()
    {
        if ( pobj )
		{
//			D del;	// error. 람다표현식이 만드는 타입은 디폴트 생성자가 없다.
			del(pobj);
		}
    }
	T& operator*()  const { return *pobj; }
    T* operator->() const { return pobj; }
};
int main()
{
	// error. 템플릿인자는 타입이 필요, 람다표현식의 결과는 객체..
//	unique_ptr<int, [](int* p) { free(p); } > p1(static_cast<int*>(malloc(sizeof(int))));
	// C++17 까지는 람다표현식은 평가되지 않은 표현식에 넣을수 없다.
//	unique_ptr<int, decltype([](int* p) { free(p); }) > p1(static_cast<int*>(malloc(sizeof(int))));

	auto del = [](int* p) { free(p); };
	unique_ptr<int, decltype(del) > p1(static_cast<int*>(malloc(sizeof(int))), del );
	unique_ptr<int, decltype(del) > p2(static_cast<int*>(malloc(sizeof(int))), std::move(del) );
}

