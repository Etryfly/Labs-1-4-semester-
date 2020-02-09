#include <string.h>
#include <memory.h>
#include <stdlib.h>
#include <stdio.h>
#include <strings.h>
#include <stdarg.h>

#define BIG_INT_DEFAULT_SIZE 1

typedef struct bigInt {
    char* data;
    long size;
    int base;
} BigInt;



BigInt* createBigInt(int base) {
    BigInt *result = malloc(sizeof(BigInt));
    result->data = NULL;
    result->data = malloc(sizeof(char) * BIG_INT_DEFAULT_SIZE);
    for (int i = 0; i < BIG_INT_DEFAULT_SIZE; ++i) {
        result->data[i] = '0';
    }
    result->base = base;
    result->size = BIG_INT_DEFAULT_SIZE;
    return result;
}

BigInt* intToBigInt(int num, int base) {
    BigInt* big = createBigInt(base);
    int i = 0;
    int n = num;
    while (n != 0) {
        n/=base;
        i++;
    }

    if (i > big->size) big = realloc(big, sizeof(char) * i);

    sprintf(big->data, "%d", num);
    big->size = i;
    return big;
}

void shiftRight(BigInt* big) {
    char* buf = malloc(sizeof(big->data) + sizeof(char));
    strcpy(buf, "0");
    strcat(buf, big->data);
    strcpy(big->data, buf);
    free(buf);
}

int charToInt(char ch) {
    return ch - '0';
}

void removeBigInt(BigInt* big) {
    free(big->data);
    free(big);
}

BigInt* sumBig(BigInt *a, BigInt *b, int base) {
    int lenA = strlen(a->data) - 1;
    int lenB = strlen(b->data) - 1;

    BigInt *result = createBigInt(base);
    int resultLen = (lenA > lenB) ? lenA : lenB;

    result->size = resultLen ;
    for (int i = 0; i < result->size; ++i) {
        shiftRight(result);
    }

    while (lenA >= 0 || lenB >= 0) {
        int sum = ((lenA >= 0) ? charToInt(a->data[lenA]) : 0 ) + ((lenB >= 0) ? charToInt(b->data[lenB]) : 0);
        if (sum + charToInt(result->data[resultLen]) >= base) {
            while (1) {
                int sum = ((lenA >= 0) ? charToInt(a->data[lenA]) : 0 ) + ((lenB >= 0) ? charToInt(b->data[lenB]) : 0);
                if (sum + charToInt(result->data[resultLen]) < base) {
                    result->data[resultLen] += sum;
                    break;
                } else {
                    int mem = (sum + charToInt(result->data[resultLen])) / base;
                    result->data[resultLen] = (sum + charToInt(result->data[resultLen])) % base + '0';
                    result->data[resultLen - 1] += mem;
                }
                resultLen--;
                lenA--;
                lenB--;
                if (resultLen < 0) {
                    shiftRight(result);
                    resultLen++;
                    result->data[resultLen] +=1;
                    break;
                }
            }
        } else {
            result->data[resultLen] += sum;
        }
        resultLen--;
        lenA--;
        lenB--;
    }
    removeBigInt(a);
    removeBigInt(b);
    result->size = strlen(result->data);
    return result;
}

BigInt* sum(int base, int n,...) {
    va_list args;
    va_start(args, n);
    BigInt* result = va_arg(args, BigInt*);

    for (int i = 1; i < n; ++i) {
        BigInt* big = va_arg(args, BigInt*);
        BigInt* r = createBigInt(base);

        strcpy(r->data, result->data);

        BigInt *tmp = sumBig(r, big, base);
        strcpy(result->data, tmp->data);
        removeBigInt(tmp);
    }
    va_end(args);
    return result;
}

int main() {
    int base = 10;
    BigInt *a = intToBigInt(2001, base);
    BigInt *b = intToBigInt(22111, base);
    BigInt *c = intToBigInt(33333, base);
    BigInt *d = intToBigInt(23456123, base);
    BigInt *e = intToBigInt(10000000, base);

    BigInt *result = sum(base, 5, a,b,c,d,e);
    printf("%s\n", result->data);

    removeBigInt(a);
    removeBigInt(b);
    removeBigInt(c);
    removeBigInt(d);
    removeBigInt(e);
    removeBigInt(result);


}