all: start

solver.exe:
	g++ main.cpp -o solver.exe -I./include

start: solver.exe
	./solver.exe
	python3.10 plotter.py
	eog plot.svg

clean:
	rm *.exe *.o *.bin *.svg
