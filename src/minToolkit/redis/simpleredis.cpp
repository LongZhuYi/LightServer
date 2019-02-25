#include "simpleredis.h"
#include <stdlib.h>

SimpleRedis::SimpleRedis( std::string host, int port ):m_host(host), m_port(port)
{
}

int SimpleRedis::HGet(const std::string sTableName, const std::string sKey, std::string& value)
{	
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	redisContext * ctx = redisConnectWithTimeout(m_host.c_str(), m_port, timeout);
	if( ctx == NULL || ctx->err )
	{
		printf("redisConnectWithTimeout fail\n");
		return -1;
	}

	std::string Cmd = "hget " + sTableName + " " + sKey;
	printf("HGet Cmd:%s\n",Cmd.c_str() );
	redisReply *reply = (redisReply *)redisCommand(ctx, Cmd.c_str());
	value.append( reply->str, reply->len );
	freeReplyObject(reply);
	return 0;
}

int SimpleRedis::HSet(const std::string sTableName, const std::string sKey, std::string value)
{
	struct timeval timeout = { 1, 500000 }; // 1.5 seconds
	redisContext * ctx = redisConnectWithTimeout(m_host.c_str(), m_port, timeout);
	if( ctx == NULL || ctx->err )
	{
		printf("redisConnectWithTimeout fail\n");
		return -1;
	}
	std::string Cmd = "hset " + sTableName + " " + sKey + " " + value;
	printf("HSet Cmd:%s\n", Cmd.c_str());
	redisReply *reply = (redisReply *)redisCommand(ctx, Cmd.c_str());
	//int iRet = reply->err;
	freeReplyObject(reply);
	return 0;
}