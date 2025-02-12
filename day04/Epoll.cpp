#include "Epoll.h"

#include <cstring>
#include <unistd.h>

#include "ErrorIf.h"

#define MAX_EVENTS 1000

Epoll::Epoll():epfd(-1),events(NULL)
{
    epfd=epoll_create1(0);
    ErrorIf(epfd==-1,"epoll _create");
    events=new epoll_event[MAX_EVENTS];
    memset(events,0,sizeof(*events)*MAX_EVENTS);
}

void Epoll::AddFd(int fd,uint32_t op)
{
    epoll_event ev;
    memset(&ev,0,sizeof(ev));
    ev.data.fd=fd;
    ev.events=op;
    ErrorIf(epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&ev)==-1,"epoll_add");
}

std::vector<epoll_event> Epoll::poll(int timeout)
{
    std::vector<epoll_event> evs;
    int nfds = epoll_wait(epfd, events, MAX_EVENTS, timeout);
    ErrorIf(nfds == -1, "epoll wait error");
    for(int i = 0; i < nfds; ++i){
        evs.push_back(events[i]);
    }
    return evs;
}

Epoll::~Epoll()
{
    if(epfd!=-1)
    {
        close(epfd);
        epfd=-1;
    }
    delete []events;
}