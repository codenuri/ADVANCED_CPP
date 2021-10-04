#pragma once

#include <iostream>

class Car
{
public:
	~Car()    { std::cout << "~Car()" << std::endl; }
	void Go() { std::cout << "Car Go()" << std::endl; }
};
