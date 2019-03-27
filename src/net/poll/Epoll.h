#program once

#include "../../base/NonCopyAble.h"
#include "../Channel.h"

extern "C"
{
	#include <stdio.h>
	#include <unistd.h>
	#include <sys/epoll.h>
}

/*
	EPOLL_CTL_ADD：往事件表中注册fd上的事件
	EPOLL_CTL_MOD：修改fd上的注册事件
	EPOLL_CTL_DEL：删除fd上的注册事件

	EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
	EPOLLOUT：表示对应的文件描述符可以写；
	EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
	EPOLLERR：表示对应的文件描述符发生错误；
	EPOLLHUP：表示对应的文件描述符被挂断；
	EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
	EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里

	typedef union epoll_data {
		void *ptr;
		int fd;
		__uint32_t u32;
		__uint64_t u64;
	} epoll_data_t;

	struct epoll_event {
		__uint32_t events; // Epoll events
		epoll_data_t data; // User data variable
	};
*/

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