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

class PipeBuffer
{
protected:
	Buffer buffer{1024};
};

class PipeStream : public PipeBuffer, public Stream
{
public:
	PipeStream() : Stream(buffer) {} // => PipeBuffer(),  Stream(buffer) {}
};

int main()
{
	PipeStream ps;
}
