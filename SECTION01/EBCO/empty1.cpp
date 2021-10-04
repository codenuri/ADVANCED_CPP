#include <iostream>
#include <type_traits>

class Empty {};

class NoEmpty 
{
    int data;
};

int main()
{
    Empty e;

    std::cout << sizeof(Empty)   << std::endl; // 1
    std::cout << sizeof(NoEmpty) << std::endl; // 4

    std::cout << std::boolalpha;
    std::cout << std::is_empty<Empty>::value << std::endl; // true
    std::cout << std::is_empty_v<Empty>      << std::endl; // true
    std::cout << std::is_empty_v<NoEmpty>    << std::endl; // false
}