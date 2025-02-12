#define PORT 8080

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>

#include "ErrorIf.h"
#include "InetAddress.h"
#include "TCPSocket.h"
#include "Epoll.h"

int main()
{
    InetAddress seraddr(PORT);
    InetAddress cliaddr;
    TCPSocket sock;
    sock.Bind(seraddr);
    sock.Listen();
    int clifd=sock.Accept(cliaddr);
    printf("fd:%d\nip:%s\nport:%d\n",clifd,inet_ntoa(cliaddr.GetAddr().sin_addr),ntohs(cliaddr.GetAddr().sin_port));
    close(clifd);
    return 0;
}