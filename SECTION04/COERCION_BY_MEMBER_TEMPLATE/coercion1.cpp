
template<typename T> class smartptr
{
	T* ptr = nullptr;
public:
	smartptr() = default;
	smartptr(T* p) : ptr(p) {}

	// 소멸자, 참조계수 기법 등.. 구현 생략..
};

int main()
{
	smartptr<int> sp(new int);
}
