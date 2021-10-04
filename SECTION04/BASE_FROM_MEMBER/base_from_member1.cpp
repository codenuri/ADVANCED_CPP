#include <iostream>

class Buffer
{
public:
	Buffer(std::size_t size)  { std::cout << "Initialize Buffer" << std::endl; }
};

class Stream
{
public:
	Stream(Buffer& buf) { std::cout << "Stream'ctor use Buffer" << std::endl;}
};

int main()
{
	Buffer buf(1024);
	Stream s(buf);
}
