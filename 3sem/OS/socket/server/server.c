#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <zconf.h>
#include <sys/wait.h>

#include "../Package.h"

#define QUEUE_SIZE 10



int main()
{
    int sock, listener;
    struct sockaddr_in addr; // структура с адресом
    Package* package = malloc(sizeof(Package));

    int bytes_read;


    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0)
    {
        perror("socket");
        exit(1);
    }

    addr.sin_family = AF_INET;
    addr.sin_port = htons(3425);
    addr.sin_addr.s_addr = inet_addr("127.0.0.2");
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        exit(2);
    }

    listen(listener, QUEUE_SIZE);

//    while(1)
//    {
        sock = accept(listener, NULL, NULL);
        if(sock < 0)
        {
            perror("Прием входящих подключений");
            exit(3);
        }
        int pid;
        switch(pid = fork())
        {
            case -1:
                perror("fork");
                break;
            case 0:
                close(listener);

                printf("Waiting...\n");
                recv(sock, package, sizeof(Package), 0);

                char fileName[1024];
                strcpy(fileName, package->data);
                recv(sock, package, sizeof(Package), 0);
                printf("Package №%d, Command Number: %d\n", package->number, package->command);



                FILE* file = fopen(fileName, "w");
                if (file == NULL) {
                    printf("Couldn't open file\n");

                } else {
                    int size = package->size;
                    for (int j = 0; j < size; ++j) {
                        fprintf(file, "%c", package->data[j]);
                    }
                    for (int i = 0; i < package->count - 1; ++i) {
                        recv(sock, package, sizeof(Package), 0);
                        size = package->size;
                        for (int j = 0; j < size; ++j) {
                            fprintf(file, "%c", package->data[j]);
                        }
                        printf("Package №%d, Command Number: %d\n", package->number, package->command);
                    }
                }
                fclose(file);
                package->number = 1;
                package->count = 1;
                package->command = SEND_CONFIRM;
                strcpy(package->data, "SERVER RECV FILE!!1!");
                send(sock, package, sizeof(Package), 0);

                recv(sock, package, sizeof(Package), 0);
                if (package->command == SEND_STOP) {
                    printf("STOP\n");
                }




                close(sock);
                _exit(0);
            default:
                close(sock);
                waitpid(pid, NULL, 0);
        }
//    }

    return 0;
}