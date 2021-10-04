#include <vector>

class Car { };

std::vector<Car*> v;

void foo()
{
	Car* p1 = new Car;

	v.push_back(p1);

	// p1 이 더이상 필요 없다면 지워도 될까 ?
	delete p1;
}
int main()
{
	foo();
}
