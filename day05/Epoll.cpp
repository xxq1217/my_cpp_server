#include "Epoll.h"

#include <cstring>
#include <unistd.h>

#include "ErrorIf.h"
#include "Channel.h"

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

std::vector<Channel*> Epoll::poll(int timeout)
{
    std::vector<Channel*> chs;
    int nfds = epoll_wait(epfd,events,MAX_EVENTS,timeout);
    ErrorIf(nfds == -1, "epoll wait error");
    for(int i=0;i<nfds;i++)
    {
        Channel* ch=(Channel*)events->data.ptr;
        ch->SetRevents(events[i].events);
        chs.push_back(ch);
    }
    return chs;
}

void Epoll::updateChannel(Channel* ch)
{
    int fd = ch->GetFd();
    struct epoll_event ev;
    bzero(&ev, sizeof(ev));
    ev.data.ptr = ch;
    ev.events = ch->GetEvents();
    if(!ch->GetInEpoll())
    {
        ErrorIf(epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &ev) == -1, "epoll add error");
        ch->SetInEpoll();
    }
    else
    {
        ErrorIf(epoll_ctl(epfd, EPOLL_CTL_MOD, fd, &ev) == -1, "epoll modify error");
    }
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