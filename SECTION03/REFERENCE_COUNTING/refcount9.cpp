#include <iostream>
#include <atomic>

class RefCountBase
{
protected:
	mutable std::atomic<int> refcnt {0};
public:
	void addRef() const
	{
		refcnt.fetch_add(1, std::memory_order_relaxed);
	}
};

template<typename T> class RefCount : public RefCountBase
{
public:
	void release() const
	{
		int ret = refcnt.fetch_sub(1, std::memory_order_acq_rel);

		if ( ret == 1 )
			delete static_cast<const T*>(this);
	}
};

class Truck : public RefCount< Truck >
{
public:
	~Truck() { std::cout << "~Truck" << std::endl; }
};

template<typename T> class AutoPtr
{
	T* obj;
public:
	explicit AutoPtr(T* p = nullptr) : obj(p) { if ( obj ) obj->addRef();}
	AutoPtr(const AutoPtr<T>& ap) : obj(ap.obj) { if ( obj ) obj->addRef();}
	~AutoPtr() { if ( obj ) if (obj ) obj->release();}
};

int main()
{
	AutoPtr<Truck> p1(new Truck);
	AutoPtr<Truck> p2 = p1;

/*
	Truck* p1 = new Truck;
	p1->addRef();
	Truck* p2 = p1;
	p2->addRef();

	p2->release();
	p1->release();
*/
}
