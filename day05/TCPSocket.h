#pragma once

class InetAddress;

class TCPSocket
{
private:
    int fd;
public:
    TCPSocket();
    TCPSocket(int);
    void Bind(InetAddress&);
    void Listen();
    int Accept();
    int Accept(InetAddress&);
    void SetNonBlocking();
    int GetFd();
    ~TCPSocket();
};
