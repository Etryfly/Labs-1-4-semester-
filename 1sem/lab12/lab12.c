//Задание: Выбрать идущие подряд тройки цифр, упорядоченных по возрастанию.
//Ввод:124 125 122 121 130 132 135 136
//Вывод:124 125 130 132 135 136


#include <stdio.h>
#include <malloc.h>


int main() {
    int c;
    int flag = 1;
    int result[3];
    int count = 0;
    int digit = 0;
    int prev = -999999999;
    while(flag) {

        c = getchar();
            if (c == EOF || c == '\n') flag = 0;
            if (c >= '0' && c <= '9') {
                c = c - '0';
                digit = digit * 10 + c;
            }


        if (c == ' ' || flag == 0) {
            if (digit > prev) {
                result[count] = digit;
                prev = digit;
                count++;

            }
            digit = 0;
            if (count == 3) {

                for (int i = 0; i < 3; ++i) {
                    printf("%d ",result[i]);
                }
                count = 0;

            }
        }
    }
}