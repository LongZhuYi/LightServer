#pragma once

#include "Poll.h"
#include <vector>
#include <map>

namespace LightServer
{
	namespace Net
	{
		class Channel;

		class Poll : public NonCopyAble
		{
		public:
			
		protected:
			virtual int Update( std::shared_ptr<Channel>& channelPtr) = 0;
			virtual int GetActivityChannelList(uint32_t timeStamp, ChannelList& channelList) = 0;
		}
	}
}