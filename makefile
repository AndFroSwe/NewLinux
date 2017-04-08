CC = gcc
LIBS = -lcurses -lmenu

newlinux.out: src/newlinux_curses.c
	$(CC) -o $@ $^ $(LIBS)

clean:
	rm *.out *.o -rf
