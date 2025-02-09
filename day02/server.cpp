#define PORT 8080

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>

#include "Errorif.h"

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
    Errorif(serfd==-1,"socket");
    Errorif(bind(serfd,(sockaddr*)&seraddr,sizeof(seraddr))==-1,"bind");
    Errorif(listen(serfd,SOMAXCONN)==-1,"listen");
    int clifd=accept(serfd,(sockaddr*)&cliaddr,&clilen);
    Errorif(clifd==-1,"accept");
    printf("fd:%d\nip:%s\nport:%d\n",clifd,inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
    close(clifd);
    close(serfd);
    return 0;
}