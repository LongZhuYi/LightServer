#pragma once

#include "../base/NonCopyAble.h"
#include <vector>
#include <functional>
#include <mutex>
#include <memory>

namespace LightServer
{
	namespace Net
	{
		class Poll;
		class Channel;

		class EventLoop : public NonCopyAble
		{
		public:
			typedef std::function< void() > Func;
			typedef std::vector< Func > FuncList;
			
			EventLoop(std::shared_ptr<Poll>& pollPtr);
			~EventLoop();

			bool UpdateChannel(Channel* channelPtr);
			void RemoveFromLoop(int fd);
			void Loop();
			bool RunInDelayFuncList( Func&& func );
		private:
			bool bStop_;
			FuncList delayFuncList_;
			std::shared_ptr<Poll> ptrPoll_;
			std::mutex mutex_;
		};
	}
}