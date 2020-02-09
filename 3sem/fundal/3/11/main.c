#pragma warning(disable: 4996)

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSTRUCTION_LENGTH 50
#define COMMANDS_COUNT 3

#define ISVALID(c) (isalpha(c) || c == ' ' || c == '\n')


const char *commands[COMMANDS_COUNT] =
        {
                "TAKE", "PUT", "MOVE"
        }, **cm;

void error() {
    printf("error\n");
    exit(-666);
}


// 001 - GOAT
// 010 - WOLF
// 100 - CABBAGE
int objToNum(char* obj) {
    if (strcmp(obj, "GOAT") == 0) return 1;
    if (strcmp(obj, "WOLF") == 0) return 2;
    if (strcmp(obj, "CABBAGE") == 0) return 4;
    return 0;
}

int main(int argc, char *argv[]) {
    FILE *fIn;
    char c;
    char buf[MAX_INSTRUCTION_LENGTH], *b = buf;

    //STATES
    int left = 7; // 111
    int right = 0;
    int boat = 0;
    int side = 0; // 0 or 1 == left or right

    if (!(fIn = fopen(argv[1], "r"))) {
        printf("Couldn't open file");
        exit(-1);
    }

    while (!feof(fIn)) {
        c = fgetc(fIn);
        if (c == EOF) break;
        if (ISVALID(c) ) {
            if (b - buf == MAX_INSTRUCTION_LENGTH - 1) {
                error();
            }
            if (c == '\n') continue;
            *b++ = toupper(c);
        } else if (c == ';') {
            *b = 0;
            b = buf;
            if (!isalpha(*b++)) {
                error();
            }
            if (isalpha(*b)) {
                for (cm = commands; cm - commands < COMMANDS_COUNT; cm++) {
                    if (strstr(buf, *cm) == buf) {
                        break;
                    }
                }
                int commandId;
                if ((commandId = cm - commands) == COMMANDS_COUNT) {
                    error();
                }

                char objName[50];
                switch (commandId) {
                    case 0:
                        if (boat != 0) error();
                        while (*b != ' ') {
                            if (*b == ';') error();
                            b++;
                        }
                        b++;

                        sscanf(b, "%s", objName);
                        int binObj = objToNum(objName);
                        if (binObj == 0) error();
                        boat = binObj;

                        if (side == 0 && left >= binObj) left -= binObj;
                        else if (side == 1 && right >= binObj) right -= binObj;
                        else error();
                        break;

                    case 1:
                        if (boat == 0) error();

                        if (side == 0) left += boat;
                        else right +=boat;

                        boat = 0;
                        break;

                    case 2:
                        if (side == 0) side = 1;
                        else side = 0;

                        break;
                }

                if (right == 7) {
                    printf("+++\n");
                    fclose(fIn);
                    return 0;
                }

                if ( (left == 3 || left == 5) && side == 1 ) {
                    printf("---\n");
                    fclose(fIn);
                    return 0;
                }


                if ( (right == 3 || right == 5) && side == 0 ) {
                    printf("---\n");
                    fclose(fIn);
                    return 0;
                }

                b = buf;
            }
        } else {
            error();
        }
    }


    fclose(fIn);
    printf("Задача не выполнена\n");

    return 0;
}

