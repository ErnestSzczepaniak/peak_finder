
files := 	main.cpp \
			source/display.cpp \
			source/block.cpp \
			source/perlin.cpp \
			source/generator.cpp


all:
	g++ -g -std=c++1z $(files) -lX11 -Iinclude/ -o peak_finder.elf