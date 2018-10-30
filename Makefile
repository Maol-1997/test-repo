servidor: petverif.o resp.o servidor.o
	gcc -Wall -o index *.c -lpthread
clean:
	rm *.o index
