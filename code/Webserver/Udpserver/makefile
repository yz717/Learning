CC = g++
.PHONY:all
all : udpClient udpServer

udpClient:udpClient.cc
	$(CC) -o $@ $^ -std=c++11 
udpServer:udpServer.cc 
	$(CC) -o $@ $^ -std=c++11 

.PHONY:clean
clean:
	rm -rf udpClient udpServer
