#include <iostream>

template<typename T>
class RefCount
{
	int refcnt = 0;
public:
	void addRef() { ++refcnt; }

	void release()    // void release(RefCount* this)
	{
		if ( --refcnt == 0 )
//			delete this;
			delete static_cast<T*>(this);
	}
protected:
	~RefCount() { std::cout << "~RefCount" << std::endl; }
};

class Truck : public RefCount< Truck >
{
public:
	~Truck() { std::cout << "~Truck" << std::endl;}
};
class Car : public RefCount<Car>
{
};

int main()
{
	Truck* p1 = new Truck;
	p1->addRef();
	p1->release();
}
