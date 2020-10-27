compiler = g++
NAME = shape_app

all: main.o
	$(compiler) main.o -L lib/ -lshape -o $(NAME)
# the name -lshape is generated from libshape.so

main.o: main.cpp
	$(compiler) -c main.cpp -I lib/

clean:
	rm main.o
	rm $(NAME)