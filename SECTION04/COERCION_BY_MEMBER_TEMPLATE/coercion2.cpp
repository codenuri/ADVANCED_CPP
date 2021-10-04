class Animal {};
class Dog : public Animal {};

template<typename T> class smartptr
{
	T* ptr = nullptr;
public:
	smartptr() = default;
	smartptr(T* p) : ptr(p) {}
};

int main()
{
	Dog*    p1 = new Dog;
	Animal* p2 = p1;

	smartptr<Dog>    sp1(new Dog);
	smartptr<Animal> sp2 = sp1;

}
