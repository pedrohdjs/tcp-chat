.PHONY: server client all runserver runclient

server:
	g++ \
		./src/server/main.cpp \
		./src/shared/Socket.cpp \
		-o ./dist/server

client:
	g++ \
		./src/client/main.cpp \
		./src/shared/Socket.cpp \
		-o ./dist/client


all: 
	make server
	make client

runserver: 
	./dist/server

runclient:
	./dist/client