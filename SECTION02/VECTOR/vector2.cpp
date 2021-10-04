#include <iostream>
#include "Point.h"

template<typename T> class Vector
{
	T* buff;
	std::size_t size;
	std::size_t capacity;
public:


	Vector(std::size_t sz, const T& value = T() ) : size(sz), capacity(sz)
	{
		buff = static_cast<Point*>(operator new(sizeof(Point) * sz));

		int i = 0;
		try
		{
			for( i = 0; i < sz; i++)
			{
	//			new(&buff[i]) T; // 디폴트 생성자 호출
				new(&buff[i]) T(value); // 복사 생성자 호출
			}
		}
		catch(...)
		{
			for( int j = i-1; j >= 0; --j)
				buff[j].~T();

			operator delete(buff);
			size = 0;
			capacity = 0;

			throw;
		}
	}

	~Vector()
	{
		for( int j = size-1; j >= 0; --j)
			buff[j].~T();

		operator delete(buff);
	}
};
int main()
{
	Point pt(0,0);
	Vector<Point> v(10, pt);

}
