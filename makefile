.PHONY: server client all runserver runclient

server:
	mkdir -p dist \
	&& \
	g++ \
		./src/server/main.cpp \
		./src/server/lib/Server.cpp \
		./src/server/lib/Client.cpp \
		./src/server/lib/Chatroom.cpp \
		./src/shared/Utils.cpp \
		./src/shared/Socket.cpp \
		-pthread \
		-o ./dist/server

client:
	mkdir -p dist \
	&& \
	g++ \
		./src/client/main.cpp \
		./src/client/lib/Action.cpp \
		./src/shared/Socket.cpp \
		./src/shared/Utils.cpp \
		-pthread \
		-o ./dist/client

all: 
	make server
	make client

runserver: 
	./dist/server

runclient:
	./dist/client