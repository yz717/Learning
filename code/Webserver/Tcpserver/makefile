CC = g++
.PHONY:all
all : tcpClient tcpServer

tcpClient:tcpClient.cc
	$(CC) -o $@ $^ -std=c++11 
tcpServer:tcpServer.cc 
	$(CC) -o $@ $^ -std=c++11 

.PHONY:clean
clean:
	rm -rf tcpClient tcpServer
