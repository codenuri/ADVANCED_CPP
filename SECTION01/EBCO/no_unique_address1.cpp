#include <iostream>

struct Empty {};

struct Data
{
    [[no_unique_address]] Empty  e;    
    int data;
};

int main()
{
    Data d;
    std::cout << sizeof(Data) << std::endl; // 8    
                                            // 4

    std::cout << &(d.e)    << std::endl;
    std::cout << &(d.data) << std::endl;
}
