all: server client

server: server.cpp ErrorIf.cpp InetAddress.cpp TCPSocket.cpp Epoll.cpp Channel.cpp
	g++ server.cpp ErrorIf.cpp InetAddress.cpp TCPSocket.cpp Epoll.cpp Channel.cpp -o server

client: client.cpp ErrorIf.cpp
	g++ client.cpp ErrorIf.cpp -o client

clean:
	rm -f server client
