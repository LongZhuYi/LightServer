#program once

#include "../../base/NonCopyAble.h"
#include "../Channel.h"

#include <sys/epoll.h>

namespace LightServer
{
	namespace Net
	{
		class Epoll : public Poll
		{
		public:
			typedef std::vector< std::shared_ptr<Channel> > ChannelList;

			Epoll();
			~Epoll();
		protected:
			virtual int Update(Channel*);
			virtual int Delete(Channel*);
			virtual int Add(Channel*);
			virtual int GetActivityChannel();
			virtual int GetActivityChannelList(uint32_t timeStamp, ChannelList& channelList);
			Channel* FindChannel( uint32_t channelID );
		private:
			ChannelList channelList_;
		}
	}
}