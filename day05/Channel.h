#pragma once

#include <sys/epoll.h>
#include <functional>

class Epoll;

class Channel
{
private:
    int fd;
    Epoll *ep;
    bool inEpoll;
    uint32_t events;
    uint32_t revents;
public:
    Channel(Epoll*,int);
    ~Channel();
    int GetFd();
    uint32_t GetEvents();
    uint32_t GetRevents();
    bool GetInEpoll();
    void SetInEpoll();
    void SetRevents(uint32_t);
    void enableReading();
};
