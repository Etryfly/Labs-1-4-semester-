
#include <stdbool.h>
#include <stdarg.h>
#include <stdlib.h>
#include <printf.h>
#include <stdio.h>

bool isIntInArray(double num, double* arr, int size) {
    for (int i = 0; i < size; ++i)
        if (arr[i] == num) return 1;

    return 0;
}

double isSimple(int base, double num) {
    int max_size = 10;


    double* arr = malloc(sizeof(double) * max_size);

    for (int j = 0; j < max_size; ++j) {
        arr[j] = 0;
    }
    double *ptr = arr;
    double flo = num;
    double chisl = flo;
    int znam = 1;
    bool isFind = 0;
    while (chisl != ((int) chisl)) {
        chisl *= 10;
        znam *= 10;
    }

    int chisl_number = (int) chisl;

    double a0 = chisl_number % znam;
    if (a0 != 0) arr[0] = a0;
    else {
        return flo;
    }
    ptr++;
    int curSize = 0;
    while (chisl_number != 0) {
        int ost = ((chisl_number)*base) % znam;
        if (ost == 0) return flo;
        if (!isIntInArray(ost, arr, max_size)) {
            if (curSize >= max_size) {
                max_size*=2;
                arr = realloc(arr, sizeof(double) * max_size);
            }

            *ptr = ost;
            curSize++;
            ptr++;
        } else {
            return 0;
        }

        chisl_number = ost;
    }
    free(arr);
    return flo;
}

double Simple(int base, int n,...) {
    va_list args;
    va_start(args, n);
    bool isFind = 0;
    double result = 0.;
    for (int i = 0; i < n; ++i) {
        if (0 != (result = isSimple(base, va_arg(args, double)))) {
            break;
        }
    }
    va_end(args);
    return result;
}

int main() {
    printf("Base: 3, num: 0.3, 0.5 result:%lf\n", Simple(3, 2, 0.3, 0.5));
    printf("Base: 2, num: 0.6, 0.125 result:%lf\n", Simple(2, 2, 0.6, 0.125));
    printf("Base: 5, num: 1, 0.5 result:%lf\n", Simple(5, 2, 1., 0.5));

}

