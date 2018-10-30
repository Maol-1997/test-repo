#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <unistd.h>
#include "resp.h"
#include "petverif.h"
#include <string.h>

#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
#include <pthread.h>

void peticion(int connfd){
	char buff[1000];
	read(connfd,buff ,sizeof buff);
	char * dir;
	strtok(buff," ");
	dir = strtok(NULL," ");
	printf("antes de la funcion respuesta");
	respuesta(dir,verificar(connfd,dir),tamano(dir),connfd);
	printf("despues de la funcion respuesta");
	pthread_exit(NULL);
}
int verificar(int connfd, char* direccion){
	int abrir = open(direccion, O_RDONLY);
	if(abrir < 0)
	return 1;
	else
	return 0;
}
int tamano(char* direccion){
	struct stat peso;
	//peso = malloc(sizeof(struct stat));
	printf("antes de abrir");
	int abrir = open(direccion, O_RDONLY);
	fstat(abrir,&peso);
	printf("despues de abrir");
	return peso.st_size;
}
