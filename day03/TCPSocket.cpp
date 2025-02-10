#include "TCPSocket.h"

#include <unistd.h>
#include <sys/socket.h>

#include "ErrorIf.h"
#include "InetAddress.h"

TCPSocket::TCPSocket()
{
    fd=socket(AF_INET,SOCK_STREAM,0);
    ErrorIf(fd==-1,"socket");
}

void TCPSocket::Bind(InetAddress& inet)
{
    ErrorIf(bind(fd,inet.ToSockaddrPtr(),inet.GetLen())==-1,"bind");
}

void TCPSocket::Listen()
{
    ErrorIf(listen(fd,SOMAXCONN)==-1,"listen");
}

int TCPSocket::Accept(InetAddress& inet)
{
    ErrorIf(accept(fd,inet.ToSockaddrPtr(),inet.GetLenPtr()),"accept");
    return 0;
}

int TCPSocket::GetFd()
{
    return fd;
}

TCPSocket::~TCPSocket()
{
    if(fd!=-1)
    {
        close(fd);
        fd=-1;
    }
}
