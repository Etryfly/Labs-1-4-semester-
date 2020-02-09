
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define SIZE_OF_NAMES 250

typedef struct passenger {
    int number;
    char* nameFrom;
    char* nameTo;
    char* cityFrom;
    char* cityTo;
    struct tm *timeFrom;
    struct tm *timeTo;
} Passenger;

typedef struct p {
    int curSize;
    int size;
    Passenger* passengers;
} Passengers;

void addToPassengers(Passengers* passengers, int number, char* nameFrom, char* cityFrom,char*  nameTo,
        char* cityTo,int h1,int m1,int h2,int m2 ) {
    Passenger* ptr = passengers->passengers;

    if (passengers->size == passengers->curSize) {
        passengers->size *= 2;
        passengers->passengers = realloc(passengers->passengers, sizeof(Passenger) * passengers->size);
        ptr = passengers->passengers;
    }
    ptr += passengers->curSize;
    struct tm *timeFrom = malloc(sizeof(struct tm));
    struct tm *timeTo = malloc(sizeof(struct tm));
    timeFrom->tm_hour = h1;
    timeFrom->tm_min = m1;

    timeTo->tm_hour = h2;
    timeTo->tm_min = m2;

    ptr->cityFrom = cityFrom;
    ptr->cityTo = cityTo;
    ptr->nameFrom = nameFrom;
    ptr->nameTo = nameTo;
    ptr->number = number;
    ptr->timeFrom = timeFrom;
    ptr->timeTo = timeTo;
    passengers->curSize++;
}

int main(int argc, char* argv[]) {
    FILE* file;
    if (!(file = fopen(argv[1], "r"))) {
        printf("Couldn't open file");
        return -1;
    }

    Passengers *passengers = malloc(sizeof(Passengers));
    passengers->size = 10;
    passengers->curSize = 0;
    passengers->passengers = malloc(sizeof(Passenger) * passengers->size);


    /*
     * Загрузка из файла
     *
     */

    int h1;
    int h2;
    int m1;
    int m2;
    int number;
    char bufNameFrom[SIZE_OF_NAMES];
    char bufNameTo[SIZE_OF_NAMES];
    char bufCityFrom[SIZE_OF_NAMES];
    char bufCityTo[SIZE_OF_NAMES];
    while (!feof(file)) {

        fscanf(file, "%d %s %s %s %s %d:%d %d:%d\n", &number, bufNameFrom, bufCityFrom, bufNameTo, bufCityTo, &h1, &m1, &h2, &m2);
        char *nameFrom = malloc(sizeof(char) * (strlen(bufNameFrom)+1));
        char *cityFrom = malloc(sizeof(char) * (strlen(bufCityFrom)+1));
        char *nameTo = malloc(sizeof(char) * (strlen(bufNameTo)+1));
        char *cityTo = malloc(sizeof(char) * (strlen(bufCityTo)+1));
        strcpy(nameFrom,bufNameFrom);
        strcpy(nameTo,bufNameTo);
        strcpy(cityFrom,bufCityFrom);
        strcpy(cityTo,bufCityTo);
        addToPassengers(passengers, number, nameFrom, cityFrom, nameTo, cityTo, h1, m1, h2, m2);
    }
    fclose(file);

    /*
     * Модификация пользователем
     * 1. Добавление
     * 2. Просмотр
     * 3. Удаление
     * 4. Выход с сохранением данных в файл
     */
    while (1) {
        printf("Комманды:\n1. Добавление\n"
               "2. Просмотр\n"
               "3. Удаление\n"
               "4. Выход\n");

        int command = 0;
        scanf("%d", &command);

        switch (command) {
            case 1: {
//                char bufNameFrom[SIZE_OF_NAMES];
//                char bufNameTo[SIZE_OF_NAMES];
//                char bufCityFrom[SIZE_OF_NAMES];
//                char bufCityTo[SIZE_OF_NAMES];

                scanf("%d %s %s %s %s %d:%d %d:%d", &number, bufNameFrom, bufCityFrom, bufNameTo, bufCityTo, &h1, &m1, &h2, &m2);

                char *nameFrom = malloc(sizeof(char) * (strlen(bufNameFrom)+1));
                char *cityFrom = malloc(sizeof(char) * (strlen(bufCityFrom)+1));
                char *nameTo = malloc(sizeof(char) * (strlen(bufNameTo)+1));
                char *cityTo = malloc(sizeof(char) * (strlen(bufCityTo)+1));
                strcpy(nameFrom,bufNameFrom);
                strcpy(nameTo,bufNameTo);
                strcpy(cityFrom,bufCityFrom);
                strcpy(cityTo,bufCityTo);

                addToPassengers(passengers, number, nameFrom, cityFrom, nameTo, cityTo, h1, m1, h2, m2);
                break;

                case 2: {
                    Passenger *ptr = passengers->passengers;
                    printf("Номер рейса | Аэропорт -> | Город -> | Аэропорт <- | Город <- | Время -> | Время <- \n");
                    for (int i = 0; i < passengers->curSize; ++i) {
                        printf("%d | %s | %s | %s | %s | %d:%d | %d:%d\n", ptr->number, ptr->nameFrom, ptr->cityFrom,
                               ptr->nameTo, ptr->cityTo, ptr->timeFrom->tm_hour, ptr->timeFrom->tm_min,
                               ptr->timeTo->tm_hour, ptr->timeTo->tm_min);
                        ptr++;
                    }
                    break;
                }

                case 3: {
                    if (passengers->curSize > 0) {
                        int n;
                        scanf("%d", &n);

                        Passenger *ptr = passengers->passengers;
                        for (int i = 0; i < passengers->curSize; ++i) {
                            if (ptr->number == n) {
                                if (ptr != passengers->passengers) {
                                    while ((ptr + 1) != passengers->passengers + passengers->curSize) {
                                        *ptr = *(ptr + 1);
                                        ptr++;
                                    }
                                } else {
                                    while ((ptr) != passengers->passengers + passengers->curSize) {
                                        *ptr = *(ptr + 1);
                                        ptr++;
                                    }
                                }
                                passengers->curSize--;
                                break;
                            }
                            ptr++;
                        }
                    } else {
                        printf("Нет записей о пассажирах для удаления");
                    }
                    break;
                }

                case 4: {
                    if (!(file = fopen(argv[1], "w"))) {
                        printf("Couldn't open file!");
                        Passenger *ptr = passengers->passengers;
                        for (int i = 0; i < passengers->curSize; ++i) {
                            free(ptr->timeTo);
                            free(ptr->timeFrom);
                            free(ptr->cityTo);
                            free(ptr->cityFrom);
                            free(ptr->nameTo);
                            free(ptr->nameFrom);
                            ptr++;
                        }
                        free(passengers->passengers);
                        return -1;
                    }
                    Passenger *ptr = passengers->passengers;
                    for (int i = 0; i < passengers->curSize; ++i) {
                        fprintf(file, "%d %s %s %s %s %d:%d %d:%d\n", ptr->number, ptr->nameFrom, ptr->cityFrom,
                                ptr->nameTo, ptr->cityTo, ptr->timeFrom->tm_hour, ptr->timeFrom->tm_min,
                                ptr->timeTo->tm_hour, ptr->timeTo->tm_min);
                        ptr++;
                    }
                    exit(0);

                }
            }
        }
    }

}