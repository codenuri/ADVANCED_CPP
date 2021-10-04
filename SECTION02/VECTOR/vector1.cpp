#include <iostream>
#include "Point.h"

template<typename T> class Vector
{
	T* buff;
	std::size_t size;
	std::size_t capacity;
public:
	Vector(std::size_t sz)
		: size(sz), capacity(sz)
	{
	//	buff = new T[sz];
		buff = static_cast<Point*>(operator new(sizeof(Point) * sz));
	}
	~Vector()
	{
	//	delete[] buff;
		operator delete(buff);
	}
};

int main()
{
	Vector<Point> v(10);

}
