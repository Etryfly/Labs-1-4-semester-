#pragma warning(disable: 4996)

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define MAX_INSTRUCTION_LENGTH 20
#define COMMANDS_COUNT 12

#define ISVALID(c) (isalnum(c) || c == ' ' || c == ',' || c == '(' || c == '+' || c == '-')

const char* errors[] =
        {
                "Input file not found",
                "Output file can't be created",
                "  ",
                "  ",
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


Var vars[27];

void error(int errorId);

void setVar(char var, int* value, int size) {
    for (int i = 0; i < 27 + 1; ++i) {
        if (vars[i].name == var) {
            vars[i].data = value;
            vars[i].size = size;
            return;
        }
    }

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
    for (int i = 0; i < 27; ++i) {
        if (vars[i].name == var) return vars[i];
    }
    error(9);
}

char** getArguments(char* str) {//input str IN format COMMAND ARG1, ARG2, ARG3, ARG4
    char* ptr = str;
    while (*ptr++ != ' ');
    char **result = malloc(sizeof(char*));
    int size = 1;
    int curSize = 0;
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
            if (size == curSize) {
                size++;
                result = realloc(result, sizeof(char*) * size);
                resPtr = result + curSize;
            }
            *resPtr = (char*)malloc(sizeof(char)* (strlen(buf) + 1));
            curSize++;
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
    result = realloc(result, sizeof(char*) * (curSize + 1));

    result[curSize] = NULL;
    return result;
}

int comparePlus(const int *a, const int *b) {
    return *a - *b;
}

int compareMinus(const int *a, const int *b) {
    return *b - *a;
}

char **arguments = NULL;

void freeArguments(char** arguments) {
    char** ptr = arguments;
    while (*ptr) {
        free(*ptr);
        ptr++;
    }
    free(arguments);
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

    srand(time(NULL));

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

                if (commandId != 4) {
                    arguments = getArguments(buf);
                }
                switch (commandId) {
                    case 0: { // read
                        if (arguments[0] && arguments[1]) {
                            char *varName = arguments[0];
                            char *fileName = arguments[1];
                            FILE* IN;
                            if (!(IN = fopen(fileName, "r"))) {
                                error(0);
                            }
                            int num = 0;
                            int *arr = malloc(sizeof(int));
                            int *arrPtr = arr;
                            int size = 1;
                            int curSize = 0;
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
                            fclose(IN);
                            setVar(varName[0], arr, curSize);
                            freeArguments(arguments);

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
                                error(0);
                            }

                            for (int i = 0; i < arr.size; ++i) {
                                fprintf(OUT, "%d ", arr.data[i]);
                            }

                            fclose(OUT);
                            freeArguments(arguments);
                        } else error(8);
                        break;
                    }

                    case 2: {
                        if (arguments[0] && arguments[1] && arguments[2] && arguments[3]) {
                            char *varName = arguments[0];
                            int count = strToInt(arguments[1]);
                            int lb = strToInt(arguments[2]);
                            int lr = strToInt(arguments[3]);
                            int *result = malloc(sizeof(int) * count);

                            for (int i = 0; i < count; ++i) {
                                result[i] = rand() % (lr - lb) + lb;
                            }
                            setVar(varName[0], result, count);
                            freeArguments(arguments);
                            break;
                        } else error(8);
                    }

                    case 3: {
                        if (arguments[0] && arguments[1]) {
                            Var A = getVar(arguments[0][0]);
                            Var B = getVar(arguments[1][0]);
                            A.data = realloc(A.data, sizeof(int) * (A.size + B.size));
                            int *ptr = A.data;
                            ptr += A.size;
                            A.size = A.size + B.size;


                            for (int i = 0; i < B.size; ++i) {
                                *ptr++ = B.data[i];
                            }
                            setVar(arguments[0][0], A.data, A.size);
                            freeArguments(arguments);
                            break;
                        } else error(8);
                    }

                    case 4: {
                        b = buf;
                        while (*b != '(') b++;
                        char var = *++b;
                        for (int i = 0; i < 27; ++i) {
                            if (vars[i].name == var) {
                                free(vars[i].data);
                                vars[i].size = 0;
                                break;
                            }
                        }
                        break;
                    }

                    case 5: {
                        if (arguments[0] && arguments[1]) {
                            char varName = arguments[0][0];
                            int l = strToInt(arguments[1]);
                            int count = strToInt(arguments[2]);
                            Var arr = getVar(varName);
                            arr.size = arr.size - count;

                            for (int i = 0; i < count; ++i) {
                                arr.data[l + i] = arr.data[l + i + count];
                            }
                            arr.data = realloc(arr.data, sizeof(int) * arr.size);
                            setVar(arr.name, arr.data, arr.size);
                            freeArguments(arguments);
                            break;
                        } else error(8);
                    }

                    case 6: {
                        if (arguments[0] && arguments[1] && arguments[2] && arguments[3]) {
                            Var varA = getVar(arguments[0][0]);
                            int l = strToInt(arguments[1]);
                            int r = strToInt(arguments[2]);
                            if (r > varA.size) error(6);
                            int *result = malloc(sizeof(int) * (r - l + 1));
                            int *resPtr = result;
                            for (int i = l; i <= r; ++i) {
                                *resPtr++ = varA.data[i];
                            }

                            setVar(arguments[3][0], result, r - l + 1);
                            freeArguments(arguments);
                            break;
                        } else error(8);
                    }

                    case 7: {
                        if (arguments[0]) {
                            Var var = getVar(arguments[0][0]);

                            if (arguments[0][1] == '+') {
                                qsort(var.data, var.size, sizeof(int),
                                      (int (*)(const void *, const void *)) comparePlus);
                            } else if (arguments[0][1] == '-') {
                                qsort(var.data, var.size, sizeof(int),
                                      (int (*)(const void *, const void *)) compareMinus);
                            } else error(6);
                            setVar(var.name, var.data, var.size);
                            freeArguments(arguments);
                            break;
                        } else error(8);
                    }

                    case 8: {
                        if (arguments[0]) {
                            Var var = getVar(arguments[0][0]);
                            int num;
                            for (int i = 0; i < var.size; ++i) {
                                num = rand() % var.size;
                                int tmp = var.data[i];
                                var.data[i] = var.data[num];
                                var.data[num] = tmp;
                            }
                            setVar(var.name, var.data, var.size);
                            freeArguments(arguments);
                            break;
                        } else error(8);

                    }

                    case 9: {
                        if (arguments[0]) {
                            Var var = getVar(arguments[0][0]);

                            int size = var.size;
                            int max = var.data[0];
                            int Imax = 0;
                            int min = var.data[0];
                            int Imin = 0;
                            for (int i = 0; i < size; ++i) {
                                if (var.data[i] > max) {
                                    max = var.data[i];
                                    Imax = i;
                                }
                                if (var.data[i] < min) {
                                    min = var.data[i];
                                    Imin = i;
                                }
                            }

                            int number = var.data[0];
                            int count = 0;
                            int maxCount = 0;
                            for (int j = 0; j < size; ++j) {
                                for (int i = j + 1; i < size; ++i) {
                                    if (var.data[i] == var.data[j]) {
                                        count++;
                                    }
                                }
                                if (count > maxCount) {
                                    number = var.data[j];
                                    maxCount = count;
                                    count = 0;
                                }
                            }

                            int sum = 0;
                            for (int k = 0; k < size; ++k) {
                                sum += var.data[k];
                            }

                            int sr = sum / size;

                            int d = 0;
                            for (int l = 0; l < size; ++l) {
                                if (abs(var.data[l] - sr) > d) {
                                    d = abs(var.data[l] - sr);
                                }
                            }

                            printf("%d %d %d %d %d %d %d %d\n", size, max, min, Imax, Imin, number, sr, d);
                            freeArguments(arguments);
                            break;
                        } else error(8);
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
                        freeArguments(arguments);
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

    for (int m = 0; m < 27; ++m) {
        free(vars[m].data);
    }

    fclose(fIn);
    return 0;
}

void error(int errorId)
{
    freeArguments(arguments);
    printf("Error #%d: %s!!1!1 Press any key to exit...", errorId, errors[errorId - 1]);
    getchar();
    exit(errorId);
}