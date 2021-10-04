#include <iostream>
#include <string>
#include <type_traits>

class Point
{
    int x{0};
    int y{0};
public:
    Point() = default;
    Point(int x, int y) : x(x), y(y) {}
};

struct one_and_variadic_arg_t  { explicit one_and_variadic_arg_t() = default; };
struct zero_and_variadic_arg_t { explicit zero_and_variadic_arg_t() = default;};



template<typename T1, typename T2, bool = std::is_empty_v<T1> > struct compressed_pair;

template<typename T1, typename T2> struct compressed_pair<T1, T2, false>
{
	T1 first;
	T2 second;

	T1& getFirst()  { return first; }
    T2& getSecond() { return second; }
	const T1& getFirst()  const { return first; }
	const T2& getSecond() const { return second; }

    template<typename A1, typename ... A2>
	compressed_pair( one_and_variadic_arg_t, A1&& arg1, A2&& ... arg2) 
        : first( std::forward<A1>(arg1) ), second( std::forward<A2>(arg2)... ) {}

    template<typename ... A2>
	compressed_pair( zero_and_variadic_arg_t, A2&& ... arg2) 
        : first(), second( std::forward<A2>(arg2)... ) {}
};

int main()
{
	compressed_pair<int, Point> cp1( one_and_variadic_arg_t{}, 1, Point(0,0));
    compressed_pair<int, Point> cp2( one_and_variadic_arg_t{}, 1, 0, 0);
    compressed_pair<int, Point> cp3( zero_and_variadic_arg_t{}, 0, 0);
}