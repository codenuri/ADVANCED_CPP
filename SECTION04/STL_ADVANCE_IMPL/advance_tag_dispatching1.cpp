#include <iostream>
#include <vector>
#include <list>
#include <iterator>

/*
// 1. empty class 를 사용해서 반복자의 종류(category) 를 타입화 한다.
struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag : input_iterator_tag {};
struct bidirectional_iterator_tag : forward_iterator_tag{};
struct random_access_iterator_tag : bidirectional_iterator_tag {};



// 2. 각 컨테이너의 반복자 설계시 해당 반복자가 어떤 종류(category) 인지
//    약속된 형태(iterator_category) 로 외부에 알려 준다.
template<typename T> class vector_iterator
{
public:
// 	using iterator_category = random_access_iterator_tag; // C++11 이후

	typedef random_access_iterator_tag iterator_category;

	// ....
};

template<typename T> class list_iterator
{
public:
// 	using iterator_category = bidirectional_iterator_tag; // C++11 이후

	typedef bidirectional_iterator_tag iterator_category;
};
*/





// 3. 반복자의 종류에 따라 다르게 동작하는 advance_imp() 함수 제공
template<typename T>
void advance_imp(T& it, std::size_t sz, std::random_access_iterator_tag)
{
	it = it + sz;
	std::cout << "using +" << std::endl;
}

template<typename T>
void advance_imp(T& it, std::size_t sz, std::input_iterator_tag)
{
	while(sz--)
		++it;
	std::cout << "using ++" << std::endl;
}

// 4. advance() 함수에서 전달된 반복자안의 "iterator_category" 에 따라
//	  함수 오버로딩(tag dispatching) 기술 사용.
template<typename T>
void xadvance(T& it, std::size_t sz)
{
	advance_imp(it, sz,
		typename T::iterator_category() );
}

int main()
{
//	std::vector<int> c = {1,2,3,4,5,6,7,8,9,10};
	std::list<int>   c = {1,2,3,4,5,6,7,8,9,10};

	auto p = std::begin(c);

	xadvance(p, 5);

	std::cout << *p << std::endl;
}
