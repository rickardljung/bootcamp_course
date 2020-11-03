compiler = g++
NAME = packet_interpreter

all: main.o
	$(compiler) main.o -L wrapper/ -lpcapOpenner -o $(NAME) -lpcap

main.o: main.cpp
	$(compiler) -c main.cpp

clean:
	rm main.o
	rm $(NAME)