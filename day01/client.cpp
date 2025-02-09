#define PORT 8080

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>

int main() {
    sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd==-1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    if(connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr))==-1)
    {
        perror("connect");
        exit(EXIT_FAILURE);
    }
    close(sockfd);
    return 0;
}