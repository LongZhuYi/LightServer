#pragma once

#include "../base/NonCopyAble.h"

namespace LightServer
{
	namespace Net
	{
		class Buffer;

		template< typename Q, typename P>
		class Coder
		{
		public:
			Coder();
			~Coder();

			bool Decode(Buffer& buff, Q& objReq);
			bool Encode(Buffer& buff, P& objResp);
		private:
			/*Q objReq;
			P objResp;*/
		};
	}
}