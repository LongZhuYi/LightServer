#include "TcpServer.h"
#include "Buffer.h"
#include "Coder.h"
#include "Socket.h"
#include "Channel.h"
#include "../base/Log.h"

using namespace LightServer::Net;

TcpServer::TcpServer(int port):port_(port)
{
}


TcpServer::~TcpServer()
{
	
}

void TcpServer::Start()
{
	int fd = Socket::Listen(port_ );
	listenChannel_.reset( new Channel(loop_, fd, Channel::ChannelType::ListenChannel) );
	listenChannel_->SetConnectFunc( std::bind( &TcpServer::OnConnect, this, std::placeholders::_1 ) );
	listenChannel_->ReadAble();
	
	loop_->Loop();
}

void TcpServer::OnConnect(int fd)
{
	std::shared_ptr<Channel> ptr( new Channel(loop_, fd, Channel::ChannelType::ConnectChannel) );
	channelList_[ fd ] = ptr;
	ptr->SetMessageFunc( messageFunc_ );
	ptr->SetCloseFunc( std::bind( &TcpServer::OnClose, this,  std::placeholders::_1) );
	ptr->SetErrorFunc( std::bind( &TcpServer::OnClose, this,  std::placeholders::_1) );
	ptr->ReadAble();
}

void TcpServer::OnClose(int fd)
{
	channelList_.erase(fd);
}