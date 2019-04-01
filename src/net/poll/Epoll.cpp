#include "Epoll.h"
#include "../base/Log.h"
#include "../Channel.h"

using namespace LightServer::Net;

const static int MAX_EVENT_CNT = 1024*10;
static struct epoll_event events[ MAX_EVENT_CNT ];

Epoll::Epoll()
{
	epollFd_ = epoll_create( MAX_EVENT_CNT );
	if( epollFd_ < 0 )
	{
		LogErr("%s epoll_create fail", __func__);
		exit(-1);
	}
}

Epoll::~Epoll()
{

}

int Epoll::Update(Channel* channelPtr, bool isNew)
{
	int events = channelPtr->EventS();
	int fd = channelPtr->Fd();

	struct epoll_event event;
	event.events = events;
	event.data.ptr = channelPtr;

	if( isNew )
	{
		epoll_ctl( epollFd_, EPOLL_CTL_ADD, fd , &event);
	}else
	{
		if( events == 0)
		{
			epoll_ctl( epollFd_, EPOLL_CTL_DEL, fd, &event );
		}else
		{
			epoll_ctl( epollFd_, EPOLL_CTL_MOD, fd,  &event);
		}
	}

	return 0;
}

void Epoll::RemoveFromLoop(int fd)
{
	epoll_ctl( epollFd_, EPOLL_CTL_DEL, fd, NULL );
}

int Epoll::GetActivityChannelList(uint32_t timeStamp, ChannelList& channelList)
{
	int n = epoll_wait( epollFd_, events, MAX_EVENT_CNT, 300 );
	for( int i=0; i<n; i++ )
	{	
		struct epoll_event& ev = events[i];
		Channel* ptr =  reinterpret_cast< Channel* >(ev.data.ptr);
		ptr->SetEventS( ev.events );
		channelList.push_back( ptr );
	}

	return 0;
}