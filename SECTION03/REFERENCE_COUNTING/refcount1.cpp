#include <iostream>

class Car
{
	int speed  = 0;
	int refcnt = 0; // 핵심
public:
	void addRef() { ++refcnt; }

	void release()
	{
		if ( --refcnt == 0 )
			delete this;
	}
	~Car() { std::cout << "~Car" << std::endl; }
};

int main()
{
	Car* p1 = new Car;
	p1->addRef();

	Car* p2 = p1;
	p2->addRef();

	p2->release();
	p1->release();
}
