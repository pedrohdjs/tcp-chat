.PHONY: server client all runserver runclient

server:
	g++ \
		./src/server/main.cpp \
		./src/server/lib/Server.cpp \
		./src/server/lib/Client.cpp \
		./src/server/lib/Chatroom.cpp \
		./src/server/lib/Utils.cpp \
		./src/shared/Socket.cpp \
		-pthread \
		-o ./dist/server

client:
	g++ \
		./src/client/main.cpp \
		./src/shared/Socket.cpp \
		-pthread \
		-o ./dist/client

all: 
	make server
	make client

runserver: 
	./dist/server

runclient:
	./dist/client