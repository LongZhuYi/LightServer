#program once

#include "../base/NonCopyAble.h"
#include <vector>
#include <functional>
#include <mutex>



namespace LightServer
{
	namespace Net
	{
		class Poll;
		
		class EventLoop : public NonCopyAble
		{
		public:
			typedef std::function< void() > Func;
			typedef std::vector< Func > FuncList;
			
			EventLoop(Poll* pollPtr);
			~EventLoop();

			bool UpdateChannel(std::shared_ptr<Channel>& channelPtr);
			void Loop();
			bool RunInDelayFuncList( Func&& func );
		private:
			bool bStop_;
			FuncList delayFuncList_;
			std::shared_ptr<Poll> ptrPoll_;
			std::mutex mutex_;
		}
	}
}