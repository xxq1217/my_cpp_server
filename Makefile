server:
	g++ server.cpp -o server && g++ client.cpp -o client

clear:
	rm -f server &&rm -f client