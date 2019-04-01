#include "Socket.h"
#include "Buffer.h"

using namespace LightServer::Net;

const static int MaxBuffSize = 1024;

/*Socket::Socket(int fd):fd_(fd)
{

}

Socket::Socket(int port, std::string addr):port_(port),addr_(addr)
{
	//buffer_.reset( new Buffer );
}

Socket::~Socket()
{

}*/

int Socket::Read(int fd, std::shared_ptr<Buffer>& buffPtr)
{
	static char buff[MaxBuffSize];
	int n = recv( fd, buff, MaxBuffSize, 0);
	if( n <= 0 )
		return 0;
	buffPtr->Write( buff, n );
	return n;
}

int Socket::Write(int fd, std::shared_ptr<Buffer>& buffPtr)
{
	static char buff[MaxBuffSize];
	int n = buffPtr->Read(buff, MaxBuffSize);
	int wsz = 0;
	while( wsz < n )
		wsz += send(fd, buff, n-wsz, 0);
	return n;
}

int Socket::Connect( int port, std::string addr )
{
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));  
    servaddr.sin_family = AF_INET;  
    servaddr.sin_port = htons(port);
    inet_pton(AF_INET, addr.c_str(), &servaddr.sin_addr);
	int fd = ::socket(AF_INET, SOCK_STREAM, 0);
	SetNonBlock(fd);
	int connFd = ::connect(fd, (struct sockaddr*)&servaddr, sizeof(struct sockaddr));
	if( connFd < 0 )
	{
		LogErr("connect fail ret:%d", connFd);
		return connFd;
	}
	return connFd;
}

int Socket::Listen( int port )
{
	struct sockaddr_in servaddr;
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_port = htons( port );
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

	int fd = socket( AF_INET, SOCK_STREAM, 0 );
	SetNonBlock(fd);
	int iRet = bind( fd, (struct sockaddr*)&servaddr, sizeof(servaddr));
	if( iRet < 0)
	{
		LogErr("bind fail ret:%d", iRet);
		return iRet;
	}

	iRet = listen(fd, 10);
	if( iRet < 0 )
	{
		LogErr("listen fail ret:%d", iRet);
		return iRet;
	}

	return fd;
}

int Socket::Accept( int fd )
{
	int connFd = accept( fd, (struct sockaddr*)NULL, NULL );
	SetNonBlock(connFd);
	return connFd;
} 


int Socket::SetNonBlock(int fd)
{
	fcntl( fd, F_SETFL, O_NONBLOCK);
	return 0;
}