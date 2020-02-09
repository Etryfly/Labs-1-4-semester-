//Задание: Есть ли слово, хотя бы одна гласная которого повторяется?

#include <stdio.h>
#include <ctype.h>

const unsigned int lu = 1;

#define VOWELS (lu<<('a' << 'a') | lu<<('e' << 'a') |lu<<('i' << 'a') |lu<<('o' << 'a') |lu<<('u' << 'a') |lu<<('y' << 'a'))

unsigned int char_to_set(int c) {
    c = tolower(c);
    return (c < 'a' || c > 'z') ? 0 : lu<<(c-'a');
}

int isVowels(int c) {
    return char_to_set(c) & VOWELS;
}

int main() {
    unsigned int set = 0;
    int flag = 0;
    int c;

    while (1) {
        c = getchar();
        if (c == EOF || c == '\n') break;

        if (c != ' ' && isVowels(c)) {
            if ((set & char_to_set(c) )!= char_to_set(c)) {
                set = set | char_to_set(c);
            } else {
                printf("%s", "YES");
                flag = 1;
                break;
            }
        } else {
            if (c == ' ') set = 0;
        }
    }

    if (flag == 0) printf("%s", "NO");
}