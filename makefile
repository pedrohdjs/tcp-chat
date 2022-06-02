.PHONY: server client all runserver runclient

server:
	g++ ./server/main.cpp -o server/server

client:
	g++ ./client/main.cpp -o client/client

all: 
	make server
	make client

runserver: 
	./server/server

runclient:
	./client/client