CPP=g++
BUILD_DEST= build
INCLUDE = include
SRCS = $(wildcard *.cpp)
MAINS = $(BUILD_DEST)/main.o $(BUILD_DEST)/test.o
OBJS := $(patsubst %.cpp, $(BUILD_DEST)/%.o, $(SRCS))
OBJS := $(filter-out $(MAINS), $(OBJS))

all: create_build_dir test main

main: $(OBJS)
	g++ -o $(BUILD_DEST)/$@ $(OBJS) main.cpp

test: $(OBJS)
	g++ -o $(BUILD_DEST)/$@ $(OBJS) test.cpp

create_build_dir:
	mkdir -p $(BUILD_DEST)

$(BUILD_DEST)/%.o: %.cpp
	$(CPP) -c  $< -o $@

clean:
	rm -rf build
