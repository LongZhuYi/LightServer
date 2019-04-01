#include "Channel.h"
#include "Buffer.h"
#include "EventLoop.h"

using namespace LightServer::Net;

Channel::Channel( std::shared_ptr<EventLoop>& loop, int fd, ChannelType type):fd_(fd), isNew_(true), loop_(loop), type_(type)
{
	inBuffer_.reset( new Buffer );
	outBuffer_.reset( new Buffer );
	event_ = EPOLLET;
}

Channel::~Channel()
{
	std::cout << "~Channel" << std::endl;

}

void Channel::HandlerEvent()
{
	if( EPOLLIN & event_ )
	{
		if( type_ == ChannelType::ListenChannel )
		{
			int fd = Socket::Accept( fd_);
			connectFunc_( fd );
		}else if( type_ == ChannelType::ConnectChannel )
		{
			int n = Socket::Read( fd_, inBuffer_);
			if( n == 0 )
			{
				DisableAll();
				closeFunc_(fd_);
				LogDebug( "closeFunc_" );
				return;
			}
			messageFunc_( this, inBuffer_ );
		}
		ReadAble();
		LogDebug( "EPOLLIN" );
	}

	if( event_ & EPOLLOUT )
	{
		Socket::Write(fd_, outBuffer_);
		DisableWrite();
		ReadAble();
		LogDebug( "EPOLLOUT" );
	}

	if( event_ & EPOLLERR )
	{
		DisableAll();
		errorFunc_(fd_);
		LogDebug( "EPOLLERR" );
	}

	if (event_ & EPOLLHUP)
	{
		DisableAll();
		closeFunc_(fd_);
		LogDebug( "EPOLLHUP" );
	}
}

void Channel::SendMsg(const char* buff, int sz)
{
	LogDebug( "SendMsg" );
	outBuffer_->Write(buff, sz);
	WriteAble();
}

void Channel::Update()
{
	if( event_ != 0 )
		loop_->RunInDelayFuncList( std::move(std::bind( &EventLoop::UpdateChannel, loop_.get(), this)) );
	else
		loop_->RemoveFromLoop( fd_ );
}