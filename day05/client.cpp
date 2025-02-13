#define PORT 8080
#define BUFFER_SIZE 1024

#include <cstring>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <arpa/inet.h>

#include "ErrorIf.h"

int main() {
    sockaddr_in serv_addr;
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(PORT);
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    ErrorIf(sockfd==-1,"connect");
    ErrorIf(connect(sockfd, (sockaddr*)&serv_addr, sizeof(serv_addr))==-1,"connect");
    while(true){
        char buf[BUFFER_SIZE];
        memset(&buf,0,sizeof(buf));
        scanf("%s", buf);
        ssize_t write_bytes = write(sockfd, buf, sizeof(buf));
        if(write_bytes == -1){
            printf("socket already disconnected, can't write any more!\n");
            break;
        }
        memset(&buf,0,sizeof(buf));
        ssize_t read_bytes = read(sockfd, buf, sizeof(buf));
        if(read_bytes > 0)
        {
            printf("message from server: %s\n", buf);
        }
        else if(read_bytes == 0)
        {
            printf("server socket disconnected!\n");
            break;
        }
        else if(read_bytes == -1)
        {
            close(sockfd);
            ErrorIf(true, "socket read error");
        }
    }
    close(sockfd);
    return 0;
}