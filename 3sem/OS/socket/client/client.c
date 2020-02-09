#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "../Package.h"
#include <string.h>

Package ** queue;
int size = 0;
int first = 0;

void QUEUE_push(Package * package) {
    size++;
    queue = realloc(queue, sizeof(Package*) * size);
    queue[size - 1] = package;
}

Package* QUEUE_pop() {
    size--;
    return queue[first++];
}

int main (int argc, char **argv)
{
	Package* package = malloc(sizeof(Package));
	queue = malloc(sizeof(Package*));
	//----------------------------------------------------------------------------
	
	int sock;
	struct sockaddr_in addr;
	struct hostent* hostinfo;;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("socket");
		exit(1);
	}
	
	addr.sin_family = AF_INET;
	addr.sin_port = htons(3425);
	addr.sin_addr.s_addr = inet_addr("127.0.0.2");
	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
	{
		perror("Подключение");
		exit(2);
	}
	char command;
    char fileName[BUFSIZ];

    package->command = SEND_NAME;
    package->number = 1;
    package->count = 1;
    package->proto = 0;
    scanf("%s", fileName);
    strcpy(package->data, fileName);
    package->size = sizeof(package);
    send(sock, package, sizeof(Package), 0);
    FILE* file = fopen(fileName, "r");
    if (file == NULL) exit(-5);
    int j = 1;

    int count = 0;
    while (1) {
        Package* p = malloc(sizeof(Package));
        int i;
        for (i = 0; i < 1024 && !(feof(file)); ++i) {
            fscanf(file, "%c", &p->data[i]);
        }
        
        p->proto = 0;
        p->command = SEND_FILE;
        p->number = j++;

        p->size = (short) i;
        
        QUEUE_push(p);
        if (feof(file)) break;
    }
    count = size;
    while (size != 0) {
        Package* package = QUEUE_pop();
        package->count = count;
        if (size == 0) {
            package->size--;
        }
        printf("Package №%d, Command Number: %d\n", package->number, package->command);
        send(sock, package, sizeof(Package), 0);
    }



    recv(sock, package, sizeof(Package), 0);
    printf("Комманда %d Сообщение: %s\n", package->command, package->data); // прием сообщения от сервера


    package->command = SEND_STOP;
    package->count = 1;
    package->number = 1;
    send(sock, package, sizeof(Package), 0);
    return 0;
		
}