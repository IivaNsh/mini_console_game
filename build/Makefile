
all: mini_console_game

mini_console_game:main.o
	g++ -Wall -o mini_console_game main.o -I../include -lcurses

main.o: ../src/main.cpp
	g++ -Wall -c main.o ../src/main.cpp -I../include

clean:
	rm -rf mini_console_game main.o 