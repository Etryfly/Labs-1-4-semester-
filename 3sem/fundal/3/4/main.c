


#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

typedef struct message {
    int id;
    int len;
    char* mess;
} Message;



int main(int argc, char* argv[]) {
    int size = 10;
    int curSize = 0;
    FILE* file;
    if (!(file = fopen(argv[1], "w"))) {
        printf("Couldn't open file");
        return -1;
    }



    int id = 0, len;
    while (1) {
        Message *message = malloc(sizeof(Message));
        message->id = id++;

        message->mess = malloc(sizeof(char) * 100);
        scanf("%s", message->mess);
        len = strlen(message->mess);

        message->len = len;
        if (strcmp(message->mess, "stop") == 0){
            free(message->mess);
            free(message);
            break;
        }
        fprintf(file, "%d %s %d\n", message->id, message->mess, message->len);
        free(message->mess);
        free(message);
    }

    fclose(file);


    if (!(file = fopen(argv[1], "r"))) {
        printf("Couldn't open file");
        return -1;
    }


    Message* messages = malloc(sizeof(Message) * size);
    Message* ptr = messages;

    while (!feof(file)) {
        if (curSize == size) {
            size *= 2;
            messages = (Message* )realloc(messages, sizeof(Message) * size);
            ptr = messages + curSize;
        }

        ptr->mess = (char *) malloc(sizeof(char) * 100);

        fscanf(file, "%d %s %d", &id, ptr->mess, &len);

        ptr->id = id;
        ptr->len = len;
        fprintf(file, "%d %s %d\n", ptr->id, ptr->mess, ptr->len);
        ptr++;
        curSize++;
    }

    fclose(file);

    for (int i = 0; i < curSize; ++i) {
        free(messages[i].mess);

    }
    free(messages);
}