#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <type_traits>

template<typename T>
void xadvance(T& it, typename std::iterator_traits<T>::difference_type sz)
{
	if constexpr ( std::is_same_v<std::random_access_iterator_tag,
				typename std::iterator_traits<T>::iterator_category> )
		it = it + sz;
	else
		while( sz--)
			++it;
}

int main()
{
//	std::vector<int> c = {1,2,3,4,5,6,7,8,9,10};
	std::list<int>   c = {1,2,3,4,5,6,7,8,9,10};

	auto p = std::begin(c);

	xadvance(p, 5);

	std::cout << *p << std::endl;
}
