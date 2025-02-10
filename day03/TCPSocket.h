#pragma once

class InetAddress;

class TCPSocket
{
private:
    int fd;
public:
    TCPSocket();
    void Bind(InetAddress&);
    void Listen();
    int Accept(InetAddress&);
    void SetNonBlocking();
    int GetFd();
    ~TCPSocket();
};
