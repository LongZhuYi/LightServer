#include "Coder.h"
#include "Buffer.h"

using namespace LightServer::Net;

template<typename Q, typename P>
Coder<Q, P>::Coder()
{

}

template<typename Q, typename P>
Coder<Q, P>::~Coder()
{

}

template<typename Q, typename P>
bool Coder<Q, P>::Decode(Buffer& buff, Q& objReq)
{
	if( buff.ReadAbleSize() >= objReq.HeadSize() + objReq.MinSize() )
	{
		return true;
	}
}

template<typename Q, typename P>
bool Coder<Q, P>::Encode(Buffer& buff, P& objResp)
{
	return true;
}