CFLAGS=-Wall -Werror -Wfatal-errors

main: main.o game.o player.o TwentyFour.o stack.o node.o
	g++ -o main main.o game.o player.o TwentyFour.o stack.o node.o

main.o: main.cpp game.h player.h TwentyFour.h stack.h node.h
	g++ -c $(CFLAGS) main.cpp

game.o: game.cpp game.h player.h TwentyFour.h stack.h node.h
	g++ -c $(CFLAGS) game.cpp

player.o: player.cpp player.h
	g++ -c $(CFLAGS) player.cpp

stack.o: stack.cpp stack.h node.h
	g++ -c $(CFLAGS) stack.cpp

node.o: node.cpp node.h
	g++ -c $(CFLAGS) node.cpp

clean:
	rm -rf *.o main
