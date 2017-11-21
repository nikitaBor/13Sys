all: main.o
	gcc -o test13 main.o
main.o: main.c
	gcc -c main.c
clean: 
	rm main.o test13
run: all
	./test13
