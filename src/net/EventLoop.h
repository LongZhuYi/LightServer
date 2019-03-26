#program once

#include "../base/NonCopyAble.h"
#include <vector>
#include <functional>

class Poll;

namespace LightServer
{
	namespace Net
	{
		class EventLoop : public NonCopyAble
		{
		public:
			typedef std::function< void() > Func;
			typedef std::vector< Func > FuncList;
			
			EventLoop(Poll* pollPtr);
			~EventLoop();

			void Loop();
			bool RunInDealyFuncList( Func&& func );
		private:
			bool bStop_;
			FuncList dealyFuncList_;
			std::shared_ptr<Poll> ptrPoll_;
		}
	}
}