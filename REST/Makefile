CPP=g++
BUILD_DIR= build
SRC_DIR = src
INCLUDE_DIR = include
SRCS = $(wildcard src/*.cpp)
MAINS = $(BUILD_DIR)/main.o $(BUILD_DIR)/test.o
OBJS := $(patsubst src/%.cpp, $(BUILD_DIR)/%.o, $(SRCS))
OBJS := $(filter-out $(MAINS), $(OBJS))

all: create_build_dir main test

main: $(OBJS)
	g++ -I$(INCLUDE_DIR) -o $(BUILD_DIR)/$@ $(OBJS) src/main.cpp

test: $(OBJS)
	g++ -I$(INCLUDE_DIR) -o $(BUILD_DIR)/$@ $(OBJS) test/test.cpp

create_build_dir:
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/%.o: src/%.cpp
	$(CPP) -I$(INCLUDE_DIR) -c  $< -o $@

clean:
	rm -rf build
