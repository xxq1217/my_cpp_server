#include "InetAddress.h"

#include <cstring>

InetAddress::InetAddress():len(sizeof(addr))
{
    memset(&addr,0,len);
}

InetAddress::InetAddress(uint16_t port):len(sizeof(addr))
{
    memset(&addr,0,len);
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=INADDR_ANY;
    addr.sin_port=htons(port);
}

InetAddress::InetAddress(const char *ip, uint16_t port):len(sizeof(addr))
{
    memset(&addr,0,len);
    addr.sin_family=AF_INET;
    addr.sin_addr.s_addr=inet_addr(ip);
    addr.sin_port=htons(port);
}

sockaddr* InetAddress::ToSockaddrPtr()
{
    return (sockaddr*)&addr;
}

sockaddr_in InetAddress::GetAddr()
{
    return addr;
}

socklen_t InetAddress::GetLen()
{
    return len;
}

socklen_t *InetAddress::GetLenPtr()
{
    return &len;
}

InetAddress::~InetAddress()
{
}
