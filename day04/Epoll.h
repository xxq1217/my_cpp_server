#pragma once

#include <vector>
#include <sys/epoll.h>

class Epoll
{
private:
    int epfd;
    epoll_event *events;
public:
    Epoll();
    void AddFd(int,uint32_t);
    void DelFd();
    void ModFd();
    std::vector<epoll_event> poll(int timeout=-1);
    ~Epoll();
};