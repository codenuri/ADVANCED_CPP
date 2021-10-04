#include <iostream>
#include "Point.h"

int main()
{
	// 아래처럼 new/delete 를 사용하는 코드가 10곳에 있는데,
	// 메모리 할당/해지 방식을 변경하고 싶다면 ?
	// ==> 10곳 모두를 수정해야 한다.
	Point* p1 = new Point(1,2);

	delete p1;

	std::allocator<Point> ax;
//	MyAlloc<Point> ax;


	Point* p2 = ax.allocate(1);

	ax.construct(p2, 0, 0); // Point(0,0)
	ax.destroy(p2);

	ax.deallocate(p2, 1);
}
