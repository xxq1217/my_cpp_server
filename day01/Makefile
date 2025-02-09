all: server client

server: server.cpp Errorif.cpp
	g++ server.cpp -o server

client: client.cpp Errorif.cpp
	g++ client.cpp -o client

clean:
	rm -f server client
