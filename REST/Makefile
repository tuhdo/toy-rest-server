CC=gcc
CPP=g++
DEPS = 
OBJ = Connection.cpp Server.cpp Parser.cpp

all: main

main: $(OBJ)
	g++ -o $@ main.cpp $^

%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $<

test:  Parser.cpp
	g++ -o $@ test.cpp $^

clean:
	rm -rf *.o
