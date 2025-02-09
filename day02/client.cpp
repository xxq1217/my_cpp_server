#define PORT 8080

#include <cstring>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>

#include "Errorif.h"

int main() {
    sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    Errorif(sockfd==-1,"connect");
    Errorif(connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr))==-1,"connect");
    close(sockfd);
    return 0;
}