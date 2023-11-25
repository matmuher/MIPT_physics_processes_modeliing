all: solver.exe

SRC_DIR := ./src
INC_DIR := ./include

SRC     := $(shell find $(SRC_DIR)/*.cpp)
HEADERS := $(shell find $(INC_DIR)/*.hpp)


solver.exe: $(SRC) $(HEADERS)
	g++ $(SRC) -o solver.exe -I$(INC_DIR) -std=c++11 -ggdb

clean: clean_meta clean_bin
	rm *.exe

clean_meta:

	rm tmp -rf *.svg

clean_bin:

	rm -rf *.bin
