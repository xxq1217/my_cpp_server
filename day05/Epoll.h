#pragma once

#include <vector>
#include <sys/epoll.h>

class Channel;
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
    std::vector<Channel*> poll(int timeout=-1);
    void updateChannel(Channel*);
    ~Epoll();
};