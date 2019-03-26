//author zhuyi
//socket operator

#program once
#include "../base/NonCopyAble.h"

#include <string>

class Buff;

namespace LightServer
{
	namespace Net
	{
		class Socket : public NonCopyAble
		{
		public:
			Socket(int fd);
			Socket(int port, std::string addr);
			~Socket();
			int Read(void*, size_t sz);
			int Write(void*, size_t sz);
			int Connect();
			int Accept(); 
		private:
			int fd_;
			int port_;
			string addr_;
		};
	}
}
