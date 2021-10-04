#include <iostream>
#include <memory>

int main()
{
    unique_ptr<Car> p1(new Car);
    
    p1->Go();
    (*p1).Go();
}