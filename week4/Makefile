all: start

solver.exe: main.cpp
	g++ main.cpp -o solver.exe -I./include -std=c++11

start: solver.exe

	python3.10 plotter.py

clean: clean_meta clean_bin
	rm *.exe *.o
	
clean_meta:

	rm tmp -rf *.svg

clean_bin:

	rm *.bin
