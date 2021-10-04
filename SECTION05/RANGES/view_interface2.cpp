#include <vector>
#include <iostream>
#include <ranges>

template<typename T>
class view_interface : public std::ranges::view_base
{
	T& Cast() { return static_cast<T&>(*this); }
public:
//	int size() { return this->end() - this->begin();	}
//	int size() { return static_cast<take_view*>(this)->end()
//							- static_cast<take_view*>(this)->begin();	}

//	int size() { return static_cast<T*>(this)->end()
//								- static_cast<T*>(this)->begin();	}

	int size() { return Cast().end() - Cast().begin();}

};

template<typename T> class take_view : public view_interface<take_view<T>>
{
	T rng;
	std::size_t count;
public:
	take_view() = default;

	take_view(T r, std::size_t c) : rng(r), count(c) {}
	auto begin() { return rng.begin(); }
	auto end()   { return rng.begin() + count; }
};

template<typename T>
take_view(T&& t, std::size_t)->take_view< std::views::all_t<T> >;

template<typename T> class reverse_view : public view_interface<reverse_view<T>>
{
	T rng;
public:
	reverse_view() = default;
	reverse_view(T& r) : rng(r) {}

	auto begin() { return std::make_reverse_iterator(rng.end()); }
	auto end() { return std::make_reverse_iterator(rng.begin()); }
};
template<typename T>
reverse_view(T&&)->reverse_view<std::views::all_t<T>>;


int main()
{
	std::vector v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	take_view tv(v, 3);


	std::cout << v.size() << std::endl; // 10
	std::cout << tv.size() << std::endl; // 10

	reverse_view rv(v);
	std::cout << rv.size() << std::endl; // 10

}
