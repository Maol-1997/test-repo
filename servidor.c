#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <netdb.h>
#include "petverif.h"
#include <pthread.h>
#include <string.h>

/*struct sockaddr_in {
    short            sin_family;   // e.g. AF_INET
    unsigned short   sin_port;     // e.g. htons(3490)
    struct in_addr   sin_addr;     // see struct in_addr, below
    char             sin_zero[8];  // zero this if you want to
};
struct in_addr {
    unsigned long s_addr;  // load with inet_aton()
};*/

int main(){
	int fd, connfd;
	struct sockaddr_in procrem={};
	fd = socket(AF_INET, SOCK_STREAM, 0);
	if  (fd < 0 ){
		perror ("socket");
		return -1;
	}

	procrem.sin_family = AF_INET;
	procrem.sin_port = htons(8080);
	//procrem.sin_addr = 192.168.1.52;
	procrem.sin_addr.s_addr = htonl(INADDR_ANY);
	//inet_pton(AF_INET,"0.0.0.0", &procrem.sin_addr);
	int a;
	setsockopt(fd, SOL_SOCKET, SO_REUSEADDR,&a, sizeof a);
	if (bind(fd,(struct sockaddr *)&procrem, sizeof procrem) < 0 ) {
		perror ("bind");
                return -1;
        }

	listen(fd, 5);
printf("antes del while");
	while ( (connfd = accept(fd,NULL, 0)) > 0 ){
		//crear un hilo
		pthread_t tid;
		printf("antes del hilo");
		pthread_create(&tid, NULL, peticion, (void *) connfd);
		printf("despues del hilo");
		//peticion(connfd,buff);
		/*char * dir;
		dir = strtok(buff," ");
		dir = strtok(NULL," ");
		respuesta(dir,verificar(connfd,dir),tamano(dir),connfd);
		pthread_exit(NULL);*/
		
	}
		return 0;
}	
