run: renderer
	./renderer
	xdg-open line.ppm 2>1 >/dev/null
renderer: main.c
	gcc main.c -lm -o renderer
