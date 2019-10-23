#pragma warning(disable: 4996)

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSTRUCTION_LENGTH 20
#define COMMANDS_COUNT 12

#define ISVALID(c) (isalnum(c) || c == ' ' || c == ',')

const char* errors[] =
        {
                "Input file not found",
                "Output file can't be created",
                "Multiline comment wasn't opened",
                "Multiline comment wasn't closed",
                "Instruction is too long",
                "Invalid instruction",
                "Command not found",
                "Wrong number of arguments",
                "Wrong name of variable"
        };

const char* commands[COMMANDS_COUNT] =
        {
                "LOAD", "SAVE", "RAND", "CONCAT", "FREE", "REMOVE", "COPY", "SORT", "PERMUTE", "STAT", "PRINT"
        }, **cm;

typedef struct v {
    char name;
    int* data;
    int size;
} Var;

int freeVarPtr = 0;
Var vars[27];

void error(int errorId);

void setVar(char var, int* value, int size) {
    for (int i = 0; i < freeVarPtr + 1; ++i) {
        if (vars[i].name == var) {
            vars[i].data = value;
            vars[i].size = size - 1;
            return;
        }
    }
    vars[freeVarPtr].data = value;
    vars[freeVarPtr].name = var;
    vars[freeVarPtr].size = size;
    freeVarPtr++;
}

int strToInt(char * str) {
    int result = 0;
    char* ptr = str;
    while (*ptr) {
        result = result * 10 + (*ptr - '0');
        ptr++;
    }
    return result;
}

Var getVar(char var) {
    for (int i = 0; i < freeVarPtr + 1; ++i) {
        if (vars[i].name == var) return vars[i];
    }
    error(9);
}

char** getArguments(char* str) {//input str IN format COMMAND ARG1, ARG2, ARG3, ARG4
    char* ptr = str;
    while (*ptr++ != ' ');
    char **result = malloc(sizeof(char*) * 250);
    char** resPtr = result;


    char buf[250] = {0}, *bufPtr = buf;
    while (1) {
        while (*ptr == ' ') {
            ptr++;
        };
        if (*ptr != ',' && *ptr != 0) {
            *bufPtr++ = *ptr++;
        } else {
            bufPtr++;
            *bufPtr = 0;
            *resPtr = (char*)malloc(sizeof(char)* (strlen(buf) + 1));
            strcpy(*resPtr, buf);
            resPtr ++;
            bufPtr = buf;
            while (*bufPtr) {
                *bufPtr++ = 0;
            }
            bufPtr = buf;
            ptr++;
        }
        if (*(ptr - 1) == 0) break;
    }
    return result;
}



int main(int argc, char* argv[])
{
    FILE* fIn;
    char c;
    char buf[MAX_INSTRUCTION_LENGTH], *b = buf;
    int commandId;

    for (int i = 0; i < 27; ++i) {
        vars[i].name = (char) ('A' + i);
        vars[i].data = 0;
    }

    if (!(fIn = fopen(argv[1], "r")))
    {
        printf("Couldn't open file");
        exit(-1);
    }

    while (!feof(fIn))
    {
        c = fgetc(fIn);
       if (ISVALID(c))
        {
            if (b - buf == MAX_INSTRUCTION_LENGTH - 1)
            {
                error(5);
            }
            *b++ = toupper(c);
        }
        else if (c == ';')
        {
            *b = 0;
            b = buf;
            if (!isalpha(*b++))
            {
                error(6);
            }
            if (isalpha(*b))
            {
                for (cm = commands; cm - commands < COMMANDS_COUNT; cm++)
                {
                    if (strstr(buf, *cm) == buf)
                    {
                        break;
                    }
                }
                if ((commandId = cm - commands) == COMMANDS_COUNT)
                {
                    error(7);
                }
                char** arguments = getArguments(buf);
                switch (commandId) {
                    case 0: { // read
                        if (arguments[0] && arguments[1]) {
                            char *varName = arguments[0];
                            char *fileName = arguments[1];
                            FILE* IN;
                            if (!(IN = fopen(fileName, "r"))) {
                                //free
                                error(0);
                            }
                            int num = 0;
                            int *arr = malloc(sizeof(int));
                            int *arrPtr = arr;
                            int size = 0;
                            int curSize = 1;
                            while (!feof(IN)) {
                                fscanf(IN, "%d", &num);
                                if (size == curSize) {
                                    size++;
                                    arr = realloc(arr, sizeof(int) * size);
                                    arrPtr = arr + curSize;
                                }
                                *arrPtr++ = num;
                                curSize++;
                            }
                            setVar(varName[0], arr, curSize);
//                            fclose(IN);
                        } else {
                            error(8);
                        }
                        break;
                    }

                    case 1: {
                        if (arguments[0] && arguments[1]) {
                            char *varName = arguments[0];
                            char *fileName = arguments[1];
                            Var arr = getVar(varName[0]);
                            FILE* OUT;
                            if (!(OUT = fopen(fileName, "w"))) {
                                // free
                                error(0);
                            }

                            for (int i = 0; i < arr.size; ++i) {
                                fprintf(OUT, "%d ", arr.data[i]);
                            }

                            fclose(OUT);
                        }
                        break;
                    }



                    case 10: {
                        if (arguments[0] && arguments[1] && !arguments[2]) {
                            Var arr = getVar(arguments[0][0]);
                            if (strcmp(arguments[1], "ALL") == 0) {
                                for (int i = 0; i < arr.size; ++i) {
                                    printf("%d ", arr.data[i]);
                                }
                                printf("\n");
                            } else error(6);
                        } else if (arguments[0] && arguments[1] && arguments[2]) {
                            Var arr = getVar(arguments[0][0]);
                            for (int i = strToInt(arguments[1]); i < strToInt(arguments[2]); ++i) {
                                printf("%d ", arr.data[i]);
                            }
                            printf("\n");
                        } else {
                            error(6);
                        }
                        break;
                    }
                }
                b = buf;
            }
            else
            {
                error(6);
            }
        }
    }

    fclose(fIn);
    return 0;
}

void error(int errorId)
{
    printf("Error #%d: %s!!1!1 Press any key to exit...", errorId, errors[errorId - 1]);
    getchar();
    exit(errorId);
}