//Задание: Подсчитать число слов в комментариях ({ и } или (* и *)) в программе на Паскале
#include <stdio.h>
#include <string.h>
//Пример комментария:
//{w1 w2 w3}

enum state {
    INIT,
    inBracket
};

int main() {
    int c;
    enum state s = INIT;
    int count = 0;

    while (1) {
        c = getchar();
        if (c==EOF) break;
        switch (s) {
            case INIT:
                switch (c) {
                    case '{':
                        s = inBracket;
                        count++;
                        break;

                    case '(':
                        if (getchar() == '*') {
                            s = inBracket;
                            count++;
                        }
                    default:
                        break;
                }
                break;
            case inBracket:
                switch (c) {
                    case '}':
                        s = INIT;
                        break;

                    case ' ':
                        count++;
                        break;

                    case '*':
                        if (getchar() == ')') {
                            s = INIT;
                        }
                        break;
                    default:break;
                }
        }
    }
    printf("%d\n",count);

}

