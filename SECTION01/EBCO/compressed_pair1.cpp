#include <iostream>
#include <string>
#include <type_traits>

template<typename T1, typename T2, bool = std::is_empty_v<T1> > struct compressed_pair;

template<typename T1, typename T2> struct compressed_pair<T1, T2, false>
{
	T1 first;
	T2 second;

	T1& getFirst()  { return first; }
    T2& getSecond() { return second; }
	const T1& getFirst()  const { return first; }
	const T2& getSecond() const { return second; }

//	compressed_pair(const T1& arg1, const T2& arg2) : first(arg1), second(arg2) {}

    template<typename A1, typename A2>
	compressed_pair(A1&& arg1, A2&& arg2) 
        : first( std::forward<A1>(arg1)), second(std::forward<A2>(arg2)) {}
};

int main()
{
	compressed_pair<int, int> p1(3, 4);

    std::string s1 = "AAA";
    std::string s2 = "BBB";
    compressed_pair<std::string, std::string> p2(std::move(s1), std::move(s2));
}