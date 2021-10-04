class Animal {};
class Dog : public Animal {};

template<typename T> class smartptr
{
	T* ptr = nullptr;
public:
	smartptr() = default;
	smartptr(T* p) : ptr(p) {}

//	smartptr(const smartptr<T>& sp) {}   // 같은 타입만 받을수 있다.
//	smartptr(const smartptr<Dog>& sp) {} // smartptr<Dog>를 받을수 있다.

	// template 생성자.
	template<typename U>
	smartptr(const smartptr<U>& sp) : ptr(sp.ptr) {} //

	template<typename> friend class smartptr;
};

int main()
{
	smartptr<Dog>    sp1(new Dog);
	smartptr<Animal> sp2 = sp1;

}
