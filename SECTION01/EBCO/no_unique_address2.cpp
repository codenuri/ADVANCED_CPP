#include <iostream>

struct Empty1 {};
struct Empty2 {};

struct Data1        // sizeof : 4
{   
    [[no_unique_address]] Empty1 e1;
    [[no_unique_address]] Empty2 e2;
    int data;
};

struct Data2    // sizeof : 1
{   
    [[no_unique_address]] Empty1 e1;
};

struct Data3    // sizeof : 1
{   
    [[no_unique_address]] Empty1 e1;
    [[no_unique_address]] Empty2 e2;
};

struct Data4    // sizeof : 2
{   
    [[no_unique_address]] Empty1 e1;
    [[no_unique_address]] Empty1 e2;
};

int main()
{
    std::cout << sizeof(Data1) << std::endl;
    std::cout << sizeof(Data2) << std::endl;
    std::cout << sizeof(Data3) << std::endl;
    std::cout << sizeof(Data4) << std::endl;

    Data3 d3;
    Data4 d4;
    std::cout << &(d3.e1) << std::endl;
    std::cout << &(d3.e2) << std::endl;
    std::cout << &(d4.e1) << std::endl;
    std::cout << &(d4.e2) << std::endl;
}
