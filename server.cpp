#define PORT 8080
#define MAX_LISTEN 10

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>

int main()
{
    sockaddr_in seraddr,cliaddr;
    memset(&seraddr,0,sizeof(seraddr));
    memset(&cliaddr,0,sizeof(cliaddr));
    socklen_t clilen=sizeof(cliaddr);
    seraddr.sin_family=AF_INET;
    seraddr.sin_addr.s_addr=INADDR_ANY;
    seraddr.sin_port=htons(PORT);
    int serfd=socket(AF_INET,SOCK_STREAM,0);
    if(serfd==-1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    if(bind(serfd,(sockaddr*)&seraddr,sizeof(seraddr))==-1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }
    if(listen(serfd,MAX_LISTEN)==-1)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    int clifd=accept(serfd,(sockaddr*)&cliaddr,&clilen);
    if(clifd==-1)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }
    printf("fd:%d\nip:%s\nport:%d\n",clifd,inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
    close(clifd);
    close(serfd);
    return 0;
}