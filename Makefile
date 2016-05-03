#http://stackoverflow.com/questions/2481269/how-to-make-a-simple-c-makefile
#  There is a good example of how to fix up this makefile and the link above.
#  At this point there is not much of a need to do so


main: main.cpp
	g++ -std=c++11 main.cpp -o main

all: main ;

clean:
	rm -f main
