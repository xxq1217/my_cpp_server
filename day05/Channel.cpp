#include "Channel.h"

#include "Epoll.h"

Channel::Channel(Epoll *_ep, int _fd) : ep(_ep), fd(_fd), events(0), revents(0), inEpoll(false)
{

}

Channel::~Channel()
{
}

void Channel::enableReading(){
    events = EPOLLIN | EPOLLET;
    ep->updateChannel(this);
}

int Channel::GetFd()
{
    return fd;
}

uint32_t Channel::GetEvents()
{
    return events;
}
uint32_t Channel::GetRevents()
{
    return revents;
}

bool Channel::GetInEpoll()
{
    return inEpoll;
}

void Channel::SetInEpoll(){
    inEpoll = true;
}

void Channel::SetRevents(uint32_t _ev){
    revents = _ev;
}