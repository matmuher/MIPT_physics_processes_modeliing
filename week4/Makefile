all: start

solver.exe: main.cpp
	g++ main.cpp -o solver.exe -I./include

start: solver.exe

	python3.10 plotter.py

clean:
	rm *.exe *.o *.bin *.svg
