#pragma warning(disable: 4996)

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INSTRUCTION_LENGTH 20
#define COMMANDS_COUNT 12

#define ISVALID(c) (isalnum(c) || c == ':' || c == '=' || \
c == '+' || c == '&' || c == '-' || c == '<' || c == '>' || \
c == '~' || c == '!' || c == '?' || c == '\\' || c == ',' || \
c == '(' || c == ')')

const char* errors[] =
        {
                "Input file not found",
                "Output file can't be created",
                "Multiline comment wasn't opened",
                "Multiline comment wasn't closed",
                "Instruction is too long",
                "Invalid instruction",
                "Command not found"
        };

const char* commands[COMMANDS_COUNT] =
        {
                "+>", "+", "&", "->", "<-", "~", "<>", "!", "?", "READ", "WRITE", "\\"
        }, **cm;

typedef struct v {
    char name;
    int data;
} Var;

Var vars[27];

void setVar(char var, int value) {
    for (int i = 0; i < 27; ++i) {
        if (vars[i].name == var) {
            vars[i].data = value;
            return;
        }
    }
}

int getVar(char var) {
    for (int i = 0; i < 27; ++i) {
        if (vars[i].name == var) return vars[i].data;
    }
}

void error(int errorId);

int trace = 0;
FILE* traceFile;

int fromTenToBase(int ten, int base) {
    int tmp = ten;
    int count = 0;
    while (tmp != 0) {
        tmp /= 2;
        count ++;
    }
    int arr[count], *ptr = arr;
    int result = 0;

    while(ten != 0) {
        *ptr++ = ten % base;
        ten /= base;
    }

    for (int i = count; i >= 0 ; --i) {
        result  = result * 10 + arr[i];
    }
    return result;
}

int fromBaseToTen(int num, int base) {
    int tmp = num;
    int count = 0;
    while (tmp != 0) {
        tmp /= 10;
        count ++;
    }
    int arr[count], *ptr = arr;
    int result = 0;

    while(num != 0) {
        *ptr++ = num % 10;
        num /= 10;
    }

     for (int i = count - 1; i >= 0 ; --i) {
        result  = result * base + arr[i];
    }
    return result;
}

int main(int argc, char* argv[])
{
    FILE* fIn;
    char c;
    char buf[MAX_INSTRUCTION_LENGTH], *b = buf;
    int inMultilineComment = 0, commandId;

    if (argc > 2 && strcmp(argv[2], "/trace") == 0) {
        trace = 1;
    }

    if (trace) {
        if (!(traceFile = fopen(argv[3], "w"))) {
            printf("Couldn't open trace file");
            trace = 0;
            exit(-1);
        }
    }

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
        if (c == '%' && !inMultilineComment)
        {
            while (c != '\n' && c != EOF)
            {
                c = fgetc(fIn);
            }
        }
        else if (c == '{')
        {
            inMultilineComment++;
        }
        else if (c == '}')
        {
            inMultilineComment--;
            if (inMultilineComment == -1)
            {
                error(3);
            }
        }
        else if (c == EOF && inMultilineComment)
        {
            error(4);
        }
        else if (ISVALID(c) && !inMultilineComment)
        {
            if (b - buf == MAX_INSTRUCTION_LENGTH - 1)
            {
                error(5);
            }
            *b++ = toupper(c);
        }
        else if (c == ';' && !inMultilineComment)
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
                if (trace)fprintf(traceFile, "%s\n", buf);
                char op;
                int base = 0;
                b = buf;
                while (*b++ != '(') {

                }
                op = *b;
                if (!(isalpha(op))) error(5);
                b++; // стоит на ,
                b++; // стоит на 1 символе base
                while (*b != ')') {
                    base = base * 10 + (*b - '0');
                    b++;
                }

                switch (commandId) {
                    case 9: { // read
                        printf("Enter value of %c IN %d base:", op, base);
                        int val;
                        scanf("%d", &val);
                        val = fromBaseToTen(val, base);
                        setVar(op, val);
                        break;
                    }



                    case 10: {// write

                        printf("Value of %c:", op);
                        printf("%d\n", fromTenToBase(getVar(op), base));
                        break;
                    }
                }
                b = buf;
            }
            else if (*b == ':')
            {

                    if (trace) fprintf(traceFile, "%s\n", buf);
                    for (cm = commands; cm - commands < COMMANDS_COUNT; cm++) {
                        if (strstr(buf, *cm)) {
                            break;
                        }
                    }

                    if ((commandId = cm - commands) == COMMANDS_COUNT) {
                        error(7);
                    }

                    b = buf;

                    char var = *b;
                    while (*b++ != '=');
                    char left = *b;
                    if (left == '\\') {
                        char v = *++b;
                        int otr = getVar(v);
                        setVar(var, ~otr);
                        b = buf;
                        continue;
                    }
                    if (!isalpha(left) || left == 0) error(5);
                    while (!(isalpha(*b++)));
                    b--;
                    char right = *b;
                    if ( !isalpha(right) || right == 0 ) {
                        error(5);
                    }
                    int l = getVar(left);
                    int r = getVar(right);
                    switch (commandId) {
                        //"+>", "+", "&", "->", "<-", "~", "<>", "!", "?", "READ", "WRITE"
                        case 0:
                            setVar(var, ~(~l & r));
                            break;

                        case 1:
                            setVar(var, l | r);
                            break;


                        case 2:
                            setVar(var, l & r);
                            break;

                        case 3:
                            setVar(var, ~l & r);
                            break;

                        case 4:
                            setVar(var, l | ~r);
                            break;

                        case 5:
                            setVar(var, (l & r) | (~l & ~r));
                            break;

                        case 6:
                            setVar(var, l ^ r);
                            break;

                        case 7:
                            setVar(var, ~(l | r));
                            break;

                        case 8:
                            setVar(var, ~(l & r));
                            break;
                    }
                    b = buf;
                    continue;

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
    if (trace) fprintf(traceFile, "Error #%d: %s!!1!1 Press any key to exit...", errorId, errors[errorId - 1]);
    printf("Error #%d: %s!!1!1 Press any key to exit...", errorId, errors[errorId - 1]);
    getchar();
    exit(errorId);
}