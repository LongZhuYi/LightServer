#include "Channel.h"
#include "Buffer.h"
#include "EventLoop.h"

using namespace LightServer::Net;

Channel::Channel( std::shared_ptr<EventLoop>& loop, int fd, ChannelType type):fd_(fd), isNew_(true), loop_(loop), type_(type)
{
	inBuffer_.reset( new Buffer );
	outBuffer_.reset( new Buffer );
}

Channel::~Channel()
{
	std::cout << "~Channel" << std::endl;
}

void Channel::HandlerEvent()
{
	switch( event_ )
	{
		case EPOLLIN:
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
					closeFunc_(fd_);
					DisableAll();
					break;
				}
				messageFunc_( this, inBuffer_ );
			}
			ReadAble();
			LogDebug( "EPOLLIN" );
			break;
		}
		case EPOLLOUT:
		{
			Socket::Write(fd_, outBuffer_);
			WriteAble();
			LogDebug( "EPOLLOUT" );
			break;
		}
		case EPOLLERR:
		{
			errorFunc_(fd_);
			DisableAll();
			LogDebug( "EPOLLERR" );
			break;
		}
		case EPOLLHUP:
		{
			closeFunc_(fd_);
			DisableAll();
			LogDebug( "EPOLLHUP" );
			break;
		}
		default:
		{

		}
	}
}

void Channel::Update()
{
	loop_->RunInDelayFuncList( std::move(std::bind( &EventLoop::UpdateChannel, loop_.get(), this)) );
}