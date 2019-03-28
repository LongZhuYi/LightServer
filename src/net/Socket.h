//author zhuyi
//socket operator

#pragma once
#include "../base/NonCopyAble.h"
#include "../base/Log.h"

#include <string>
#include <iostream>
#include <memory>

extern "C"
{
	#include<stdio.h>  
	#include<stdlib.h>  
	#include<string.h>  
	#include<errno.h>  
	#include<sys/types.h>  
	#include<sys/socket.h>  
	#include<netinet/in.h>
	#include<arpa/inet.h> 
}

using namespace std;

namespace LightServer
{
	namespace Net
	{
		class Buffer;

		class Socket : public NonCopyAble
		{
		public:
			Socket(int fd);
			Socket(int port, std::string addr);
			~Socket();
			int Read(void*, size_t sz);
			int Write(void*, size_t sz);
			int Connect();
			int Listen();
			int Accept(); 
		private:
			int fd_;
			int port_;
			string addr_;

			std::unique_ptr<Buffer> buffer_;
		};
	}
}
