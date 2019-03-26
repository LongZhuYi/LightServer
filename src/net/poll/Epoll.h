#program once

#include "../../base/NonCopyAble.h"
#include "../Channel.h"

extern "C"
{
	#include <stdio.h>
	#include <unistd.h>
	#include <sys/epoll.h>
}	

namespace LightServer
{
	namespace Net
	{
		class Epoll : public Poll
		{
		public:
			typedef std::vector< std::shared_ptr<Channel> > ChannelList;

			Epoll();
			~Epoll();
		protected:
			virtual int Update(std::shared_ptr<Channel>& channelPtr, bool isNew);
			virtual int GetActivityChannelList(uint32_t timeStamp, ChannelList& channelList);
		private:
			int epollFd_;
		}
	}
}