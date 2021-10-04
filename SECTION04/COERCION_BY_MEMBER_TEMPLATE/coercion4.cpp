#include <type_traits>

class Animal {};
class Dog : public Animal {};

template<typename T> class smartptr
{
	T* ptr = nullptr;
public:
	smartptr() = default;
	smartptr(T* p) : ptr(p) {}

	template<typename U,
	         typename = std::enable_if_t<std::is_convertible_v<U*, T*> >>
	smartptr(const smartptr<U>& sp) : ptr(sp.ptr) {}

	template<typename> friend class smartptr;
};

int main()
{
	smartptr<Dog>    sp1(new Dog);
	smartptr<Animal> sp2 = sp1;

	smartptr<int>    sp3(new int);
	smartptr<double> sp4 = sp3;
}
