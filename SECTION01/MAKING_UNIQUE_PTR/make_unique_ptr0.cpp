#include <iostream>
#include <memory>

class Car
{
public:
    ~Car()    { std::cout << "~Car" << std::endl; }
    void Go() { std::cout << "Car Go" << std::endl; }
};
int main()
{
//	std::unique_ptr<Car> p = new Car; // error.
	std::unique_ptr<Car> p(new Car);  // explicit constructor

	// 포인터와 유사하게 * 와 -> 로 Car 의 멤버 접근 가능
	p->Go();
	(*p).Go();

	//  복사 할수 없지만, 이동은 가능
//	std::unique_ptr<Car> p1 = p; // error
	std::unique_ptr<Car> p2 = std::move(p); // ok

	// member function
	Car* cp = p2.get();
	p2.reset();
}