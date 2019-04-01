#include "../src/net/TcpServer.h"
#include "../src/net/poll/Epoll.h"
#include "../src/net/Socket.h"

#include <memory>
#include <iostream>

using namespace LightServer::Net;
using namespace std;

int OnRead(Channel* channel, std::shared_ptr<Buffer>& buff)
{
	std::string msg;
	if( buff->ReadAbleSize() <= 0 )
	{
		buff->Clear();
		return 0;
	}
	msg.append( buff->ReadData(), buff->ReadAbleSize() );
	buff->Clear();
	std::cout << msg << std::endl;
	std::string resp("hello world");
	channel->SendMsg( resp.data(), resp.size() );

	return 0;
}

int main(int argc, char** argv)
{
	int port = atoi( argv[1] );

	std::cout << port << std::endl;

	shared_ptr<Poll> epoll(new Epoll);
	shared_ptr<TcpServer> serverPtr(new TcpServer(port));
	shared_ptr<EventLoop> loopPtr(new EventLoop(epoll));

	serverPtr->SetMessageFunc( OnRead );
	serverPtr->SetLoop( loopPtr );
	serverPtr->Start();

	return 0;
}
