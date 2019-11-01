

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

typedef struct Node {
    char* surname;
    char* name;
    char* patronymic;
    int day;
    int year;
    int month;
    int sex;
    int salary;

    struct Node *next;
} Node;

Node* first;

Node* createNode(char* name,char* surname,  char* patronymic, int day, int year, int month, int sex, int salary) {
        Node* node = malloc(sizeof(Node));
        node->name = name;
        node->surname = surname;
        node->patronymic = patronymic;
        node->day = day;
        node->year = year;
        node->month = month;
        node->sex = sex;
        node->salary = salary;
        node->next = NULL;
        return node;
}

int compareByAge(Node* first, Node* second) {
    if (first->year > second->year) return 1;
    if (first->year < second->year) return -1;

    if (first->year == second->year) {
        if (first->month > second->month) return 1;
        if (first->month < second->month) return -1;

        if (first->month == second->month) {
            if (first->day > second->day) return 1;
            if (first->day < second->day) return -1;


        }
    }

    return 1;

}

void printAll() {
    Node* cur = first;
    printf("%15s %15s %15s %4s %4s %4s %4s %9s", "Name", "Surname", "Patronymic", "Day", "Year",
           "Month", "Sex", "Salary\n");
    while (cur != NULL) {

        printf("%15s %15s %15s %4d %4d %4d %4d %9d\n", cur->name, cur->surname, cur->patronymic, cur->day,
               cur->year, cur->month, cur->sex, cur->salary);
        cur = cur->next;
    }
}

void insertNode(Node* node) {
    Node* cur = first;
    if (cur == NULL) {
        first = node;

        return;
    }
    if (compareByAge(first, node) > 0) {
        node->next = first;
        first = node;

        return;
    }
    Node* prev = cur;
    while (cur->next != NULL) {
        if (compareByAge(cur, node) < 0) {
            prev = cur;
            cur = cur->next;
        } else {
            break;
        }
    }

    if (cur != NULL && compareByAge(cur, node) < 0) {
        cur->next = node;
        node->next = NULL;
        return;
    }

    node->next = prev->next;
    prev->next = node;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Invalid arguments");
        exit(-2);
    }
    FILE* file;
    if (!(file = fopen(argv[1], "r"))) {
        printf("Counld't open %s", argv[1]);
        exit(-1);
    }
    char nameBuf[250];
    char surnameBuf[250];
    char patronymicBuf[250];

    int day;
    int year;
    int month;
    int sex;
    int salary;

    while(!feof(file)) {
        fscanf(file, "%s %s %s %d %d %d %d %d\n", nameBuf, surnameBuf, patronymicBuf, &day, &year, &month, &sex, &salary);
        char* name = malloc(sizeof(char) * (strlen(nameBuf) + 1));
        char* surname = malloc(sizeof(char) * (strlen(surnameBuf) + 1));
        char* patronymic = malloc(sizeof(char) * (strlen(patronymicBuf) + 1));
        strcpy(name, nameBuf);
        strcpy(surname, surnameBuf);
        strcpy(patronymic, patronymicBuf);
        Node* node = createNode(name, surname, patronymic, day, year, month, sex, salary);
        insertNode(node);
    }

    fclose(file);
    int action = 0;
    char buf[250];
    while (action != 5) {
        printf("1.Print all\n"
               "2.Search\n"
               "3.Delete\n"
               "4.Add\n"
               "5.Exit\n");

        scanf("%d", &action);

        switch (action) {
            case 1: {
                printAll();
                break;
            }

            case 2:
                printf("Enter name and date in format Day Year Month\n");
                scanf("%s %d %d %d", buf, &day, &year, &month);
                Node* cur = first;
                while (cur != NULL) {
                    if (strcmp(buf, cur->name) == 0 && day == cur->day && year == cur->year && month == cur->month) {
                        printf("%15s %15s %15s %4d %4d %4d %4d %9d\n", cur->name, cur->surname, cur->patronymic, cur->day,
                               cur->year, cur->month, cur->sex, cur->salary);
                        break;
                    }

                    if (cur->next) cur = cur->next;
                }
                break;

            case 3:
                printf("Enter name\n");
                scanf("%s", buf);
                cur = first;
                Node* prev = cur;
                Node* remove;
                while (cur != NULL) {
                    if (strcmp(buf, cur->name) == 0) {
                        remove = cur;

                        if (cur == first) {
                            first = cur->next;
                        } else {
                            prev->next = cur->next;
                        }

                        free(remove->name);
                        free(remove->patronymic);
                        free(remove->surname);
                        free(remove);
                        break;
                    }

                    if (cur->next){
                        prev = cur;
                        cur = cur->next;
                    }
                }

                break;

            case 4:
                printf("Enter Name Surname Patronymic Day Year Month Sex Salary\n");
                scanf("%s %s %s %d %d %d %d %d", nameBuf, surnameBuf, patronymicBuf, &day, &year, &month, &sex, &salary);
                char* name = malloc(sizeof(char) * (strlen(nameBuf) + 1));
                char* surname = malloc(sizeof(char) * (strlen(surnameBuf) + 1));
                char* patronymic = malloc(sizeof(char) * (strlen(patronymicBuf) + 1));
                strcpy(name, nameBuf);
                strcpy(surname, surnameBuf);
                strcpy(patronymic, patronymicBuf);
                Node* node = createNode(name, surname, patronymic, day, year, month, sex, salary);
                insertNode(node);
                break;

            case 5:
                if (!(file = fopen(argv[1], "w"))) {
                    printf("Counld't open %s", argv[1]);
                    exit(-3);
                }
                cur = first;
                while (cur != NULL) {
                    fprintf(file, "%s %s %s %d %d %d %d %d\n", cur->name, cur->surname, cur->patronymic, cur->day,
                           cur->year, cur->month, cur->sex, cur->salary);
                    cur = cur->next;
                }
                return 0;
        }
    }
}