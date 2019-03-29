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

			int Write(char* ptr, unsigned int sz);
			int Read(char* ptr, unsigned int sz);

			char* ReadData(){ return data_+lpos_; }
			char* WriteData(){ return data_+rpos_; }

			unsigned int ReadAbleSize(){ return rpos_-lpos_; }
			unsigned int WriteAbleSize(){ return BuffMaxSize-rpos_; }
			void Clear(){ lpos_=0; rpos_=0; }
		private:
			char data_[ BuffMaxSize ];
			unsigned int lpos_;
			unsigned int rpos_;
		};
	}
}