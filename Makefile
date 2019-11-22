# 10 points
# Define Make rules as follows:
# A default rule to compile a .c file into a .o file
# A rule for "all" to build the entire project into a program called "game"
# A rule for "clean" to remove all .o files


all: blackjack
blackjack: game.o card.o
	cc -o blackjack game.o card.o
game.o:
	cc -c main.c
card.o:
	cc -c card.o
clean:
	rm -f *.o blackjack
run:
	./blackjack
