
files := 	main.cpp \
			source/display.cpp \
			source/generator.cpp \
			source/node.cpp \
			source/grid.cpp \
			source/algs.cpp


all:
	g++ -g -std=c++1z $(files) -lX11 -Iinclude/ -o peak_finder.elf