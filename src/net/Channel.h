#program once

#include "../base/NocCopyAble.h"
#include <>

class EventLoop;

namespace LightServer
{
	namespace Net
	{
		class Channel : public NocCopyAble
		{
		public:

			enum EventType
			{

			};

			Channel( EventLoop* loop, int fd );
			~Channel();

			int ReadAble();
			int WriteAble();
			int ConnectAble();

			int DisableAll();
			int DisableConnect();
			int DisableRead();
			int DisableWrite();
			int DelFromLoop();

			void HandlerEvent();

		private:
			int fd_;
			uint8_t event_;
			std::shared_ptr<EventLoop> loop_;
		}
	}
}