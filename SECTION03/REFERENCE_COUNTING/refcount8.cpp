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

int main()
{
	Truck* p1 = new Truck;
	p1->addRef();
	p1->release();
}
