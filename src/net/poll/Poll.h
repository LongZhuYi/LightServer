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

			virtual int Update( std::shared_ptr<Channel>& channelPtr, bool) = 0;
			virtual int GetActivityChannelList(uint32_t timeStamp, std::vector< std::shared_ptr<Channel> >& channelList) = 0;
		};
	}
}