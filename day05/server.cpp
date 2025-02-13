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
#include "Channel.h"

void handleReadEvent(int sockfd)
{
    char buf[READ_BUFFER];
    while(true)
    {
        memset(&buf,0,sizeof(buf));
        ssize_t bytes_read=read(sockfd,buf,sizeof(buf));
        if(bytes_read>0)
        {
            printf("message from client fd %d: %s\n", sockfd, buf);
            write(sockfd,buf,sizeof(buf));
        }
        else if(bytes_read==-1&&errno==EINTR)
        {
            printf("continue reading");
            continue;
        }
        else if(bytes_read==-1&&((errno==EAGAIN)||(errno==EWOULDBLOCK)))
        {
            printf("finish reading once, errno: %d\n", errno);
            break;
        }
        else if(bytes_read==0)
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
    Epoll* ep=new Epoll;
    sock.SetNonBlocking();
    sock.Bind(seraddr);
    sock.Listen();
    Channel* serch=new Channel(ep,sock.GetFd());
    ep->AddFd(sock.GetFd(),EPOLLIN|EPOLLET);
    while(true)
    {
        std::vector<Channel*>chs=ep->poll();
        //std::vector<epoll_event>evs=ep->poll();
        int nfds=chs.size();
        for(int i=0;i<nfds;i++)
        {
            if(chs.at(i)->GetFd()==sock.GetFd())
            {
                InetAddress cliaddr;
                TCPSocket* clisock=new TCPSocket(sock.Accept(cliaddr));
                printf("fd:%d\nip:%s\nport:%d\n",clisock->GetFd(),inet_ntoa(cliaddr.GetAddr().sin_addr),ntohs(cliaddr.GetAddr().sin_port));
                clisock->SetNonBlocking();
                ep->AddFd(clisock->GetFd(), EPOLLIN | EPOLLET);
            }
            else if (chs[i]->GetRevents()&EPOLLIN)
            {
                handleReadEvent(chs[i]->GetFd());
            }
            else
            {
                printf("something else happened\n");
            }
        }
    }
    delete ep;
    delete serch;
    return 0;
}