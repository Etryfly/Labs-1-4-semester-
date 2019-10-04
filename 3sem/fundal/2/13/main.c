//13. Реализовать функцию с переменным числом аргументов,
// принимающую координаты точек многоугольника и вычисляющую, является ли этот многоугольник выпуклым.

#include <stdbool.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

typedef struct _vector {
    int x;
    int y;
} Vector;

bool isCamber(int count, ...) {
    va_list args;
    va_start(args, count);
    Vector vectors[count + 2];
    for (int i = 0; i < count; ++i) {
        vectors[i].x = va_arg(args, int);
        vectors[i].y = va_arg(args, int);
    }

    vectors[count] = vectors[0]; //для проверки угла между последним и первым вектором
    vectors[count + 1] = vectors[1];

    va_end(args);
    int sign = 0;

    for (int j = 1; j < count + 1; ++j) {
        Vector* AB = malloc(sizeof(Vector));
        AB->x = vectors[j].x - vectors[j - 1].x;
        AB->y = vectors[j].y - vectors[j - 1].y;

        Vector* BC = malloc(sizeof(Vector));
        BC->x = vectors[j + 1].x - vectors[j].x;
        BC->y = vectors[j + 1].y - vectors[j].y;

        double k = AB->x * BC->y - AB->y * BC->x;
        //printf("sign: %lf\n", k);
        free(AB);
        free(BC);

        if (sign == 0) {
            sign = (int) k;
            continue;
        }
        if (k > 0 && sign < 0) return 0;
        if (k < 0 && sign > 0) return 0;
        sign = (int) k;


    }


    return 1;
}

int main() {
    printf("%d\n", isCamber(5, 2,2, 3,4, 5,2, 3,2, 2,1));
    printf("%d\n", isCamber(5, 2,2, 3,4, 5,2, 3,1, 2,1));
    printf("%d\n", isCamber(3, 2,3, 3,1, 2,2));
    printf("%d\n", isCamber(3, 2,3, 3,1, 2,2));
}