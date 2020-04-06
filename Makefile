

all:
	g++ -g -std=c++1z main.cpp source/display.cpp source/block.cpp -lX11 -Iinclude/ -o peak_finder.elf