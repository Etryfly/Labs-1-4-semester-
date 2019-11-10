#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define HASHSIZE 128
typedef struct HashNode {
    char* key;
    char* value;
    struct HashNode* next;
} HashNode;

HashNode* createNode(char* key, char* value) {
    HashNode* hashNode = malloc(sizeof(HashNode));
    hashNode->key = malloc(sizeof(char) * (strlen(key) + 1));
    hashNode->value = malloc(sizeof(char) * (strlen(value) + 1));
    strcpy(hashNode->key, key);
    strcpy(hashNode->value, value);
    hashNode->next = NULL;
    return hashNode;
}

int getHash(char* str) {
    int len = strlen(str);
    int numIn62[len], *ptrNum = numIn62;
    char* ptrStr = str;
    while (*ptrStr) {
        *ptrNum++ = *ptrStr - '0';
        ptrStr++;
    }
    int result = 0;
    for (int i = len - 1; i >= 0 ; --i) {
        result += (numIn62[i] * (int) pow(62, i)) % HASHSIZE;
    }
    return result % HASHSIZE;
}

void insertNodeInTable(HashNode* node, HashNode** table) {
    int hash = getHash(node->key);
    if (table[hash] == NULL) {
        table[hash] = node;
    } else {
        HashNode* cur = table[hash];
        while (cur->next != NULL) {
            if (cur->key == node->key) {
                cur->value = node->value;
                return;
            }
            cur = cur->next;
        }
        cur->next = node;
    }
}

HashNode* getNodeFromTableByKey(char* key, HashNode** table) {
    int hash = getHash(key);
    if (hash < 0 || hash > HASHSIZE) return NULL;
    HashNode* cur = table[hash];
    if (cur == NULL) return NULL;
    while (1) {
        if (strcmp(cur->key, key ) == 0) {
            return cur;
        } else {
            if (cur->next != NULL) {
                cur = cur->next;
            } else {
                return NULL;
            }
        }
    }
}

void freeTable(HashNode** table) {
    HashNode* cur;
    for (int i = 0; i < HASHSIZE; ++i) {
        if (table[i] != NULL) {

            cur = table[i];
            while (cur->next != NULL) {
                free(cur->value);
                free(cur->key);
                HashNode* prev = cur;
                cur = cur->next;
                free(prev);
            }
        }
    }
}

int main() {
    HashNode* table[HASHSIZE] = {NULL};
    FILE* file;
    char defineFileName[250];
    char replaceFileName[250];
    scanf("%s", defineFileName);
    scanf("%s", replaceFileName);
    if (!(file = fopen(defineFileName, "r"))) {
        exit(-1);
    }

    char buf[250];
    char key[250];
    char val[250];
    while (!(feof(file))) {
        fscanf(file, "%s", key);
        fscanf(file, "%s", key);
        fscanf(file, "%s", val);


        HashNode* node = createNode(key, val);
        insertNodeInTable(node, table);
    }
    FILE* replaceFile;
    FILE* tmpFile;

    if (!(tmpFile = fopen("tmp", "w"))) {
        exit(-2);
    }

    if (!(replaceFile = fopen(replaceFileName, "r"))) {
        exit(-3);
    }
    char c = 1;
    char* bufPtr = buf;
    *bufPtr = 0;
    int flag = 0;
    fscanf(replaceFile, "%c", &c);
    while (c != EOF) {
        if (feof(replaceFile)) c = EOF;
        if (c == ' ' || c == EOF) {
            *bufPtr = 0;
            bufPtr = buf;
            HashNode *node = getNodeFromTableByKey(buf, table);
            if (node != NULL) {
                fprintf(tmpFile, "%s ", node->value);
            } else {
                fprintf(tmpFile, "%s ", buf);
            }
//            printf("%s ", buf);

        } else if (c == '\n') {
            *bufPtr = 0;
            bufPtr = buf;
            HashNode *node = getNodeFromTableByKey(buf, table);

            if (node != NULL) {
                fprintf(tmpFile, "%s\n", node->value);
            } else {
                fprintf(tmpFile, "%s\n", buf);
            }
//            printf("%s\n", buf);

        } else {
            *bufPtr++ = c;
        }
        fscanf(replaceFile, "%c", &c);
    }

    if (!(feof(replaceFile))) {
        fscanf(replaceFile, "%c", &c);
    }

    if (!(freopen(replaceFileName,"w", replaceFile))) {
        exit(-4);
    }


    if (!(freopen("tmp","r", tmpFile))) {
        exit(-5);
    }
    char ch;
    while (!(feof(tmpFile))) {
        fscanf(tmpFile, "%c", &ch);
        fprintf(replaceFile, "%c", ch);
    }

    fclose(tmpFile);
    fclose(replaceFile);
    freeTable(table);

}