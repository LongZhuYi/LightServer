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
	#include <unistd.h>
    #include <fcntl.h>
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
			//Socket(int fd);
			//Socket(int port);
			//~Socket();
			static int Read(int fd, std::shared_ptr<Buffer>& buff);
			static int Write(int fd, std::shared_ptr<Buffer>& buff);
			static int Connect(int port, std::string addr);
			static int Listen(int fd);
			static int Accept(int fd);
			static int SetNonBlock(int fd);
		private:
			int fd_;
			int port_;
			string addr_;

			//std::unique_ptr<Buffer> buffer_;
		};
	}
}
