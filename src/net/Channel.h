#pragma once

#include "../base/NonCopyAble.h"
#include "poll/Epoll.h"
#include "Socket.h"
#include "Buffer.h"

extern "C"
{
	#include <sys/epoll.h>
}
#include <memory>

/*
EPOLLIN ：表示对应的文件描述符可以读（包括对端SOCKET正常关闭）；
EPOLLOUT：表示对应的文件描述符可以写；
EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）；
EPOLLERR：表示对应的文件描述符发生错误；
EPOLLHUP：表示对应的文件描述符被挂断；
EPOLLET： 将EPOLL设为边缘触发(Edge Triggered)模式，这是相对于水平触发(Level Triggered)来说的。
EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里
*/

namespace LightServer
{
	namespace Net
	{
		class EventLoop;
		class Buffer;
		class Channel;

		typedef std::function<int(Channel*, std::shared_ptr<Buffer>& buff)> MessageFunc;
		typedef std::function<int(int)> WriteFunc;
		typedef std::function<void(int)> ConnectFunc;
		typedef std::function<void(int)> CloseFunc;
		typedef std::function<void(int)> ErrorFunc;

		class Channel : public NonCopyAble
		{
		public:
			enum ChannelType
			{
				ConnectChannel = 0,
				ListenChannel = 1,
			};

			Channel( std::shared_ptr<EventLoop>& loop, int fd , ChannelType type);
			~Channel();

			int Fd(){ return fd_; }
			int EventS(){ return event_; }
			void SetEventS(int events){ event_ = events; }

			void ReadAble(){ event_ |= EPOLLIN; Update();  }
			void WriteAble(){ event_ |= EPOLLOUT; Update(); };

			void DisableAll(){ event_ = 0; Update(); }
			void DisableRead(){ event_ &= ~EPOLLOUT; Update();}
			void DisableWrite(){ event_ &= ~EPOLLIN; Update(); }

			void HandlerEvent();

			void SetMessageFunc( const MessageFunc& func ) { messageFunc_ = func; }
			void SetWriteFunc( const WriteFunc& func ) { writeFunc_ = func; }
			void SetConnectFunc( const ConnectFunc& func ) { connectFunc_ = func; }
			void SetErrorFunc( const ErrorFunc& func ) { errorFunc_ = func; }
			void SetCloseFunc( const CloseFunc& func ) { closeFunc_ = func; }
			void Update();

			bool IsNew(){ return isNew_; }
			void SetOld(){ isNew_ = false; }

		private:
			int fd_;
			uint8_t event_;
			bool isNew_;
			std::shared_ptr<EventLoop> loop_;
			std::shared_ptr<Buffer> inBuffer_;
			std::shared_ptr<Buffer> outBuffer_;

			MessageFunc messageFunc_;
			WriteFunc writeFunc_;
			ConnectFunc connectFunc_;
			CloseFunc closeFunc_;
			ErrorFunc errorFunc_;
			ChannelType type_; 
		};
	}
}