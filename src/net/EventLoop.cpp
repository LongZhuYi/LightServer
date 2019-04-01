#include "EventLoop.h"
#include "Channel.h"
#include "poll/Poll.h"

using namespace LightServer::Net;


EventLoop::EventLoop(std::shared_ptr<Poll>& pollPtr):bStop_(false), ptrPoll_(pollPtr)
{
}

EventLoop::~EventLoop()
{

}

bool EventLoop::UpdateChannel(Channel* channelPtr)
{
	ptrPoll_->Update( channelPtr, channelPtr->IsNew());
	channelPtr->SetOld();
	return true;
}

void EventLoop::Loop()
{
	while( !bStop_ )
	{
		FuncList tmpDelayFuncList;
		{
			std::lock_guard<std::mutex> lock(mutex_);
			tmpDelayFuncList.swap( delayFuncList_ );
			delayFuncList_.clear();
		}

		for( auto func : tmpDelayFuncList )
		{
			func();
		}

		std::vector< Channel* > channelList;
		ptrPoll_->GetActivityChannelList(300, channelList);
		for( auto channel : channelList )
		{
			channel->HandlerEvent();
		}
	}
}

bool EventLoop::RunInDelayFuncList( Func&& func )
{
	std::lock_guard< std::mutex > lock( mutex_ );
	delayFuncList_.emplace( delayFuncList_.end(), func);
	return true;
}

void EventLoop::RemoveFromLoop(int fd)
{
	ptrPoll_->RemoveFromLoop( fd );
}