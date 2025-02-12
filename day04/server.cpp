#define PORT 8080
#define MAX_EVENTS 1024
#define READ_BUFFER 1024

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>
#include <errno.h>

#include "ErrorIf.h"
#include "InetAddress.h"
#include "TCPSocket.h"
#include "Epoll.h"

void handleReadEvent(int sockfd){
    char buf[READ_BUFFER];
    while(true){
        bzero(&buf, sizeof(buf));
        ssize_t bytes_read = read(sockfd, buf, sizeof(buf));
        if(bytes_read > 0)
        {
            printf("message from client fd %d: %s\n", sockfd, buf);
            write(sockfd, buf, sizeof(buf));
        }
        else if(bytes_read == -1 && errno == EINTR)
        {
            printf("continue reading");
            continue;
        }
        else if(bytes_read == -1 && ((errno == EAGAIN) || (errno == EWOULDBLOCK)))
        {
            printf("finish reading once, errno: %d\n", errno);
            break;
        }
        else if(bytes_read == 0)
        {
            printf("EOF, client fd %d disconnected\n", sockfd);
            close(sockfd);
            break;
        }
    }
}

int main()
{
    InetAddress seraddr(PORT);
    TCPSocket sock;
    Epoll ep;
    sock.SetNonBlocking();
    sock.Bind(seraddr);
    sock.Listen();
    ep.AddFd(sock.GetFd(),EPOLLIN|EPOLLET);
    while(true)
    {
        std::vector<epoll_event>evs=ep.poll();
        int nfds=evs.size();
        for(int i=0;i<nfds;i++)
        {
            if(evs.at(i).data.fd==sock.GetFd())
            {
                InetAddress cliaddr;
                TCPSocket* clisock=new TCPSocket(sock.Accept(cliaddr));
                printf("fd:%d\nip:%s\nport:%d\n",clisock->GetFd(),inet_ntoa(cliaddr.GetAddr().sin_addr),ntohs(cliaddr.GetAddr().sin_port));
                clisock->SetNonBlocking();
                ep.AddFd(clisock->GetFd(), EPOLLIN | EPOLLET);
            }
            else if (evs[i].events&EPOLLIN)
            {
                handleReadEvent(evs[i].data.fd);
            }
            else
            {
                printf("something else happened\n");
            }
        }
    }
    return 0;
}