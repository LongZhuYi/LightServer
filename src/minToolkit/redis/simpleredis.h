#ifndef SIMPLE_REDIS_H
#define SIMPLE_REDIS_H

#include "../../../third_party/hredis/hiredis.h"
#include <string>

class SimpleRedis
{
public:
	SimpleRedis( std::string host, int port );
public:
	int HGet(const std::string sTableName, const std::string sKey, std::string& value);
	int HSet(const std::string sTableName, const std::string key, std::string value );

private:
	std::string m_host;
	int m_port;
};

#endif