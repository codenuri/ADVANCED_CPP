#include <iostream>
#include <vector>
#include <list>
#include <iterator>

/*
template<typename T> struct iterator_traits
{
	typedef typename T::iterator_category iterator_category;
};

template<typename T> struct iterator_traits<T*>
{
	typedef std::random_access_iterator_tag iterator_category;
};
*/

template<typename T>
void advance_imp(T& it, std::size_t sz, std::random_access_iterator_tag) { it = it + sz; }

template<typename T>
void advance_imp(T& it, std::size_t sz, std::input_iterator_tag) {	while(sz--)	++it; }

template<typename T>
void xadvance(T& it, std::size_t sz)
{
	//							int*::iterator_category
//	advance_imp(it, sz,	typename T::iterator_category() );
	advance_imp(it, sz,	typename std::iterator_traits<T>::iterator_category() );
}

int main()
{
//	std::vector<int> c = {1,2,3,4,5,6,7,8,9,10};
//	std::list<int>   c = {1,2,3,4,5,6,7,8,9,10};
	int c[10] = {1,2,3,4,5,6,7,8,9,10};

	auto p = std::begin(c); // p는 int*

	xadvance(p, 5);

	std::cout << *p << std::endl;
}
