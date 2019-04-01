#include "Buffer.h"
#include <algorithm>
#include <iostream>

using namespace LightServer::Net;

Buffer::Buffer():lpos_(0),rpos_(0) 
{
}

Buffer::~Buffer()
{
	std::cout << "~Buffer" << std::endl;
}

int Buffer::Write(char* ptr, unsigned int sz)
{
	sz = std::min( sz, BuffMaxSize - rpos_ );
	for(int i=0; i<sz; i++)
	{
		data_[ rpos_++ ] = *(ptr++);
	}
	return sz;
}

int Buffer::Read(char* ptr, unsigned int sz)
{
	sz = std::min(sz, rpos_-lpos_);
	for(int i=0; i<sz; i++)
	{
		*(ptr++) = data_[ lpos_++ ]; 
	}
	return sz;
}