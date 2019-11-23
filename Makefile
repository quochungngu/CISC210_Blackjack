# 10 points
# Define Make rules as follows:
# A default rule to compile a .c file into a .o file
# A rule for "all" to build the entire project into a program called "game"
# A rule for "clean" to remove all .o files


all: game
game: game.o card.o
	cc -o game game.o card.o
game.o:
	cc -c game.c
card.o:
	cc -c card.c
clean:
	rm -f *.o game
run:
	./game
test: clean all run
