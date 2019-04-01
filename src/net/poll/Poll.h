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
			typedef std::vector<Channel*> ChannelList;
			virtual int Update( Channel* channelPtr, bool) = 0;
			virtual void RemoveFromLoop(int fd) = 0;
			virtual int GetActivityChannelList(uint32_t timeStamp, ChannelList& channelList) = 0;
		};
	}
}