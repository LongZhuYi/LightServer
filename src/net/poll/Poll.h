#program once

#include "Poll.h"
#include <vector>
#include <map>

class Channel;

namespace LightServer
{
	namespace Net
	{
		class Poll : public NonCopyAble
		{
		public:
			
		protected:
			virtual int Update(Channel*) = 0;
			virtual int Delete(Channel*) = 0;
			virtual int Add(Channel*) = 0;
			virtual int GetActivityChannelList(uint32_t timeStamp, ChannelList& channelList) = 0;
		}
	}
}