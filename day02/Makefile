all: server client

server: server.cpp Errorif.cpp
	g++ server.cpp Errorif.cpp -o server

client: client.cpp Errorif.cpp
	g++ client.cpp Errorif.cpp -o client

clean:
	rm -f server client
