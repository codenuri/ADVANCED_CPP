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

class PipeStream : public Stream
{
//	Buffer buffer{1024};
	Buffer buffer;
public:
//	PipeStream() : Stream(buffer  ) {}
	PipeStream() : buffer(1024), Stream(buffer) {}
};

int main()
{
	PipeStream ps;
}
