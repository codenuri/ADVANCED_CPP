#include <iostream>
#include <functional>
#include <type_traits>

int main()
{
    std::plus<int>    f1;
    std::modulus<int> f2;

    int v = 0;
    auto f3 = [ ](int a, int b) { return a + b;};
    auto f4 = [v](int a, int b) { return a + b + v;};

    std::allocator<int> ax;

    std::cout << std::boolalpha;
    std::cout << std::is_empty_v< decltype(f1) > << std::endl;
    std::cout << std::is_empty_v< decltype(f2) > << std::endl;
    std::cout << std::is_empty_v< decltype(f3) > << std::endl;  
    std::cout << std::is_empty_v< decltype(f4) > << std::endl; // false 
    std::cout << std::is_empty_v< decltype(ax) > << std::endl;   
}