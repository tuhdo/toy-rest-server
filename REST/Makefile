CC=gcc
CPP=g++
DEPS = 
OBJ = HttpMessage.cpp Connection.cpp Server.cpp

all: main

main: $(OBJ)
	g++ -o $@ main.cpp $^

%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $<

clean:
	rm -rf *.o
