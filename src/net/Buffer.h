#pragma once

#include "../base/NonCopyAble.h"

const static unsigned int BuffMaxSize = 1024;

namespace LightServer
{
	namespace Net
	{
		class Buffer : public NonCopyAble
		{
		public:
			Buffer();
			~Buffer();

			void Write(char* ptr, unsigned int sz);
			void Read(char* ptr, unsigned int sz);

			unsigned int ReadAbleSize(){ return rpos_-lpos_; }
		private:
			char data_[ BuffMaxSize ];
			unsigned int lpos_;
			unsigned int rpos_;
		};
	}
}