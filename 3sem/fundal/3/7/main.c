

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>


typedef struct string {
    char* message;
    int len;
}String;


String* createStr(char *str) {
    int size = 0;
    size = strlen(str);
    String *result = malloc(sizeof(String));
    result->message = malloc(sizeof(char ) * (size+1));
    strcpy(result->message, str);
    result->len = size;
    return result;
}

void removeStr(String * str) {
    free(str->message);
    free(str);
}

int strCmp(String* str1, String* str2) {
    char* ptr1 = str1->message;
    char* ptr2 = str2->message;
    while (*ptr1 != 0 && *ptr2 != 0) {
        if (*ptr1++ != *ptr2++) {
            return 1;
        }
    }

    if (*ptr2 != 0 || *ptr1 != 0) return  1;
    return 0;
}

void strCat(String* dest, String* str) {
    dest->len += str->len;
    dest->message = (char *)realloc(dest->message, sizeof(char) * (dest->len+1));
    char* ptrD = dest->message;
    char* ptrS = str->message;
    while (*ptrD++ != 0);
    ptrD --;
    while (*ptrS != 0) {
        *ptrD = *ptrS;
        ptrD++;
        ptrS++;
    }
}

String* strDuplicate(String* origin) {
    String* str = createStr(origin->message);
    return str;
}

int main() {
    String* str1 = createStr("First");
    String* str11 = createStr("First");
    String* str2 = createStr("Second");
    printf("Compare %s %s: %d\n", str1->message, str11->message, strCmp(str1, str11));
    strCat(str1, str2);
    printf("Cat : %s\n",str1->message);
    String* dubl = strDuplicate(str1);
    printf("Duplicate :%s\n", dubl->message);

//    removeStr(str1);
    removeStr(dubl);
    removeStr(str11);
    removeStr(str2);

    String* test = createStr("Test");
    strCat(test, str1);
    printf("%s", test->message);
}