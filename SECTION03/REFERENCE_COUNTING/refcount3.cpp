#include <iostream>

class RefCount
{
	int refcnt = 0;
public:
	void addRef() { ++refcnt; }

	void release()    // void release(RefCount* this)
	{
		if ( --refcnt == 0 )
			delete this;
	}
protected:
	virtual ~RefCount() { std::cout << "~RefCount" << std::endl; }
};

class Truck : public RefCount
{
public:
	~Truck() { std::cout << "~Truck" << std::endl;}
};

int main()
{
	Truck* p1 = new Truck;
	p1->addRef();
	p1->release();
}
