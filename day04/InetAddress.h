#pragma once

#include <arpa/inet.h>

class InetAddress
{
private:
    sockaddr_in addr;
    socklen_t len;
public:
    InetAddress();
    InetAddress(uint16_t);
    InetAddress(const char*,uint16_t);
    sockaddr* ToSockaddrPtr();
    sockaddr_in GetAddr();
    socklen_t GetLen();
    socklen_t* GetLenPtr();
    ~InetAddress();
};