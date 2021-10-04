#include <iostream>

class RefCountBase
{
protected:
	mutable int refcnt = 0;
public:
	void addRef() const { ++refcnt; }
};

template<typename T>
class RefCount : public RefCountBase
{
public:
	void release() const
	{
		if ( --refcnt == 0 )
			delete static_cast<const T*>(this);
	}
};

class Truck : public RefCount< Truck >  { };
class Car   : public RefCount< Car >  { };

int main()
{
	Truck* p1 = new Truck;
	p1->addRef();
	p1->release();
}
