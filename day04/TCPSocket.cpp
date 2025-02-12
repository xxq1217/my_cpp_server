#include "TCPSocket.h"

#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>

#include "ErrorIf.h"
#include "InetAddress.h"

TCPSocket::TCPSocket()
{
    fd=socket(AF_INET,SOCK_STREAM,0);
    ErrorIf(fd==-1,"socket");
}

TCPSocket::TCPSocket(int clifd)
{
    fd=clifd;
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

int TCPSocket::Accept()
{
    int cliaddr=accept(fd,NULL,NULL);
    ErrorIf(cliaddr==-1,"accept");
    return cliaddr;
}

int TCPSocket::Accept(InetAddress& inet)
{
    int cliaddr=accept(fd,inet.ToSockaddrPtr(),inet.GetLenPtr());
    ErrorIf(cliaddr==-1,"accept");
    return cliaddr;
}

void TCPSocket::SetNonBlocking()
{
    fcntl(fd, F_SETFL, fcntl(fd, F_GETFL) | O_NONBLOCK);
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
