#include <iostream>
#include <vector>
#include <list>
#include <iterator>

template<typename T>
void advance_imp(T& it, typename std::iterator_traits<T>::difference_type sz, std::random_access_iterator_tag) { it = it + sz; }

template<typename T>
void advance_imp(T& it, typename std::iterator_traits<T>::difference_type sz, std::input_iterator_tag) {	while(sz--)	++it; }

template<typename T>
void xadvance(T& it, typename std::iterator_traits<T>::difference_type sz)
{
	advance_imp(it, sz,	typename std::iterator_traits<T>::iterator_category() );
}

int main()
{
	std::vector<int> c = {1,2,3,4,5,6,7,8,9,10};
//	std::list<int>   c = {1,2,3,4,5,6,7,8,9,10};
//	int c[10] = {1,2,3,4,5,6,7,8,9,10};

	auto p = std::begin(c);

	xadvance(p, 5);

	std::cout << *p << std::endl;
}
