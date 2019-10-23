

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct employee {
    int id;
    char *name;
    char *surname;
    int salary;
} Employee;


int main(int argc, char* argv[]) {
    FILE* in;
    if (argc < 3) {
        printf("Arguments missing");
        return 3;
    }
    if ( !(in = fopen(argv[1], "r"))) {
        printf("Couldn't open IN");
        return 1;
    }

    FILE* out;
    if (!(out = fopen(argv[2], "w"))) {
        printf("Couldn't open out");
        return 2;
    }
    int size = 10;
    int curSize = 0;
    int salary, id;

    char nameBuf[250];
    char surnameBuf[250];
    Employee *employees = malloc(sizeof(Employee) * size), *ptr = employees;
    while (!feof(in)) {
        if (curSize == size) {
            size *= 2;
            employees = realloc(employees, sizeof(Employee) * size);
            ptr = employees + curSize;
        }

        fscanf(in, "%d %s %s %d", &id, nameBuf, surnameBuf, &salary);

        ptr->name = malloc(sizeof(char) * (strlen(nameBuf)+1));
        strcpy(ptr->name, nameBuf);
        ptr->id = id;
        ptr->surname = malloc(sizeof(char) * (strlen(surnameBuf)+1));
        strcpy(ptr->surname, surnameBuf);
        ptr->salary = salary;
        ptr++;
        curSize ++;
    }

    fclose(in);

    for (int i = 0; i < curSize; ++i) {
        for (int j = curSize - 1; j > i ; j --) {
            if (employees[j-1].salary > employees[j].salary) {
                Employee tmp = employees[j-1];
                employees[j-1] = employees[j];
                employees[j] = tmp;
            }
        }
    }

    for (int k = 0; k < curSize; ++k) {
        fprintf(out, "%d %s %s %d\n", employees[k].id, employees[k].name, employees[k].surname, employees[k].salary);
        free(employees[k].surname);
        free(employees[k].name);
    }
    free(employees);
    fclose(out);


}

