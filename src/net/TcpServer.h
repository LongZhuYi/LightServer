#pragma once

#include "../base/NonCopyAble.h"
#include "EventLoop.h"
#include "Channel.h"
#include <memory>

namespace LightServer
{
	namespace Net
	{
		class EventLoop;
		//class Coder;
		class Channel;


		typedef std::function<int(Channel*, std::shared_ptr<Buffer>& buff)> ReadFunc;
		typedef std::function< int(int) > WriteFunc;
		typedef std::function< int(int) > MessageFunc;
		typedef std::function< int(int) > ErrorFunc;

		class TcpServer : public NonCopyAble
		{
		public:
			TcpServer(int port);
			~TcpServer();

			void Start();
			void Stop(){}
			void SetLoop(std::shared_ptr<EventLoop>& loop ){ loop_ = loop; };

			void OnConnect(int fd);

			//注册事件处理函数
			void SetReadFunc( ReadFunc&& readFunc ) { readFunc_ = readFunc; }
			void SetWriteFunc( WriteFunc&& writeFunc ) { writeFunc_ = writeFunc;  }
			void SetMessageFunc( MessageFunc&& messageFunc ) { messageFunc_ = messageFunc; }
			void SetErrorFunc( ErrorFunc&& errorFunc ) { errorFunc_ = errorFunc; } 

		private:
			std::shared_ptr<EventLoop> loop_;
			std::unique_ptr<Channel>   listenChannel_;
			//std::unique_ptr<Coder>  coder_;

			ReadFunc readFunc_;
			WriteFunc writeFunc_;
			MessageFunc messageFunc_;
			ErrorFunc errorFunc_;
			std::map<uint32_t, std::shared_ptr<Channel>> channelList_;

			int port_;
		};
	}
}