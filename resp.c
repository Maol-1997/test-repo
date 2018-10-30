#include "resp.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
void respuesta(char* direccion,int existe,int tamano,int connfd){
	char resp[1000];
	if(existe == 1)
		strcpy(resp,"HTTP/1.1 404 Not Found\n\n");
	else{
		char * tipo;
		tipo = strtok(direccion,".");
		tipo = strtok(NULL,".");
		if(strcmp(tipo,"txt") == 0)
		sprintf(resp,"HTTP/1.1 200 OK\nContent-Length: %d\nContent-Type: text/plain\n",tamano);
		if(strcmp(tipo,"jpg") == 0 || strcmp(tipo,"jpeg") == 0)
		sprintf(resp,"HTTP/1.1 200 OK\nContent-Length: %d\nContent-Type: image/jpeg\n",tamano);
		write(connfd,resp,strlen(resp));
		int abrir = open(direccion, O_RDONLY);
		char buffer[1000];
		int bytesRead;
		while((bytesRead = read(abrir,buffer,1000)) > 0){
			write(connfd,buffer,bytesRead);
		}
		close(abrir);
		write(connfd,"\n\n",2);
	}
}
