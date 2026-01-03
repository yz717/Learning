.PHONY: all clean
all: server client

client: client.cc
	g++ -o $@ $^ -std=c++11
server: server.cc
	g++ -o $@ $^ -std=c++11

clean:
	rm -rf server client