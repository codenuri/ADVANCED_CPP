#include <iostream>

struct Empty {};

// Empty 를 1번째 멤버로 포함하는 경우
struct Data1
{
    Empty e;    
    int   data;
};

// Empty 로 부터 상속 받는 경우
struct Data2 : public Empty
{
    int   data;  
};

int main()
{
    std::cout << sizeof(Data1) << std::endl; // 8
    std::cout << sizeof(Data2) << std::endl; // 4
}
