#program once

#include "../base/NocCopyAble.h"
#include "poll/Epoll.h"

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

		class Channel : public NocCopyAble
		{
		public:

			typedef std::function<void(int)> ReadFunc;
			typedef std::function<void(int)> WriteFunc;
			typedef std::function<void(int)> ErrorFunc;

			enum EventType
			{

			};

			Channel( std::shared_ptr<EventLoop>& loop, int fd );
			~Channel();

			int Fd(){ return fd_; }
			int EventS(){ return event_; }
			int SetEventS(int events){ event_ = events; }

			int ReadAble(){ event_ |= EPOLLIN; Update();  }
			int WriteAble(){ event_ |= EPOLLOUT; Update(); };

			int DisableAll(){ event_ = 0; Update(); }
			int DisableRead(){ event_ &= ~EPOLLOUT; Update();}
			int DisableWrite(){ event_ &= ~EPOLLIN; Update(); }

			void HandlerEvent();

			void SetReadFunc( ReadFunc&& func ) { readFunc_ = func; }
			void SetWriteFunc( WriteFunc&& func ) { writeFunc_ = func; }
			void SetErrorFunc( ErrorFunc&& func ) { errorFunc_ = func; }
			void Update();

		private:
			int fd_;
			uint8_t event_;
			std::shared_ptr<EventLoop> loop_;

			ReadFunc readFunc_;
			WriteFunc writeFunc_;
			ErrorFunc errorFunc_;

		}
	}
}