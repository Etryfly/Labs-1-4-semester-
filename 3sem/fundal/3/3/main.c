

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct employee {
    int id;
    char *name;
    char *surname;
    int salary;
} Employee;



Employee* createEmployee(int id, char* name, char* surname, int salary) {
    Employee *e = malloc(sizeof(Employee));
    e->id = id;
    e->name = malloc(sizeof(char) * 120);
    e->surname = malloc(sizeof(char) * 120);
    strcpy(e->name, name);
    strcpy(e->surname, surname);

    e->salary = salary;
    return e;
}

void removeEmployee(Employee* em) {
    //free(em->name);
    //free(em->surname);
    free(em);
}

int main(int argc, char* argv[]) {
    FILE* in;
    if (!(in = fopen(argv[1], "r"))) {
        printf("Couldn't open in");
        return 1;
    }

    FILE* out;
    if (!(out = fopen(argv[2], "w"))) {
        printf("Couldn't open in");
        return 1;
    }
    int size = 10;
    int curSize = 0;
    int salary, id;

    Employee **employees = malloc(sizeof(Employee *) * size), **ptr = employees;
    while (!feof(in)) {
        if (curSize == size) {
            size *= 2;
            employees = realloc(employees, sizeof(Employee*) * size);
        }
        char name[120], surname[120];
        fscanf(in, "%d %s %s %d", &id, name, surname, &salary);

        *ptr++ = createEmployee(id, name, surname, salary);
        curSize ++;
    }

    fclose(in);

    for (int i = 0; i < curSize; ++i) {
        for (int j = curSize - 1; j > i ; j --) {
            if (employees[j-1]->salary > employees[j]->salary) {
                Employee* tmp = employees[j-1];
                employees[j-1] = employees[j];
                employees[j] = tmp;
            }
        }
    }

    for (int k = 0; k < curSize; ++k) {
        fprintf(out, "%d %s %s %d\n", employees[k]->id, employees[k]->name, employees[k]->surname, employees[k]->salary);
        removeEmployee(employees[k]);
    }
    free(employees);
    fclose(out);


}

