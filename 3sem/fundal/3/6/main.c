//Файл содержит ФИО студента, группу и оценки за 5 экзаменов. Необходимо
//реализовать структуру Student с советующими полями, затем прочитать файл, заполняя
//динамический массив структур Student; в трассировочный файл вывести ФИО студента,
//группу и среднюю оценку за экзамен. Далее необходимо вывести фамилии и имена
//студентов, чей балл выше среднего за все экзамены.

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

typedef struct student {
    char* name1;
    char* name2;
    char* name3;
    int group;
    int *score;
} Student;

double mid(int score[5]) {
    int sum = 0;
    for (int i = 0; i < 5; ++i) {
        sum += score[i];
    }
    return sum / 5.;
}

void freeStudent(Student* s) {
    free(s->name1);
    free(s->name2);
    free(s->name3);
    free(s->score);

}

int main(int argc, char* argv[]) {
    FILE* file;

    if (!(file = fopen(argv[1], "r"))) {
        printf("Couldn't open file");
        exit(-1);
    }

    FILE* out;
    if (!(out = fopen(argv[2], "w"))) {
        printf("Couldn't open file");
        exit(-1);
    }

    int size = 10;
    int curSize = 0;
    int group;
    int *score;
    Student *students = malloc(sizeof(Student) * size);
    Student *ptr = students;
    int midScore[5] = {0};
    char buf1[250];
    char buf2[250];
    char buf3[250];
    while (!feof(file)) {
        if (size == curSize) {
            size *= 2;
            students = (Student *)realloc(students, sizeof(Student) * size);
            ptr = students + curSize;
        }
        score = malloc(sizeof(int) * 5);
        fscanf(file, "%s %s %s %d %d %d %d %d %d", buf1, buf2 ,buf3, &group, &score[0], &score[1],&score[2],&score[3],&score[4]);

        ptr->name1 = malloc(sizeof(char) * (strlen(buf1) + 1));
        ptr->name2 = malloc(sizeof(char) * (strlen(buf2) + 1));
        ptr->name3 = malloc(sizeof(char) * (strlen(buf3) + 1));
        strcpy(ptr->name1, buf1);
        strcpy(ptr->name2, buf2);
        strcpy(ptr->name3, buf3);
        ptr->group = group;
        ptr->score = score;
        ptr++;
        curSize++;

        fprintf(out, "%s %s %s %f\n", buf1, buf2, buf3, mid(score));
        for (int i = 0; i < 5; ++i) {
            midScore[i] += score[i];
        }
    }
    fprintf(out, "------------------------\n");
    for (int j = 0; j < 5; ++j) {
        midScore[j] /= curSize;
    }
    int isGreater;
    ptr = students;
    for (int k = 0; k < curSize; ++k) {
        isGreater = 1;
        for (int i = 0; i < 5; ++i) {
            if (ptr->score[i] <= midScore[i]) isGreater = 0;
        }
        if (isGreater) fprintf(out, "%s %s\n", ptr->name1, ptr->name2);
        ptr++;
    }
    ptr = students;
    for (int l = 0; l < curSize; ++l) {
        freeStudent(ptr++);

    }
    free(students);


}