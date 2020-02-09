#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>

#define FTOKSEMPATH "/tmp/lab6sem" /*Путь к файлу, передаваемому ftok для набора семафоров */
#define FTOKSHMPATH "/tmp/lab6shm" /*Путь к файлу, передаваемому ftok для разделяемого сегмента */
#define FTOKID 1                   /*Идентификатор, передаваемый ftok */

#define NUMSEMS 3                  /* Число семафоров в наборе */
#define SIZEOFSHMSEG 512           /* Размер сегмента разделяемой памяти */

#define NUMMSG 2                   /* Число передаваемых сообщений */

int main(void)
{
    struct sembuf operations[4];
    void         *shm_address;
    int semid, shmid;
    key_t semkey, shmkey;

    semkey = 666;
    shmkey = 6666;
//
//    /*Создание IPC-ключей*/
//    semkey = ftok(FTOKSEMPATH,FTOKID);
//    if ( semkey == (key_t)-1 )
//    {
//        printf("Клиент: ошибка при выполнении %s\n","semkey = ftok(FTOKSEMPATH,FTOKID);");
//        return -1;
//    }
//    shmkey = ftok(FTOKSHMPATH,FTOKID);
//    if ( shmkey == (key_t)-1 )
//    {
//        printf("Клиент: ошибка при выполнении %s\n","shmkey = ftok(FTOKSHMPATH,FTOKID);");
//        return -1;
//    }

    /*Получение набора семафоров с помощью IPC-ключей*/
    semid = semget( semkey, NUMSEMS, 0666);
    if ( semid == -1 )
    {
        printf("Клиент: ошибка при выполнении %s\n","semid = semget( semkey, NUMSEMS, 0666);");
        return -1;
    }

    /*Получение сегмента разделяемой памяти*/
    shmid = shmget(shmkey, SIZEOFSHMSEG, 0666);
    if (shmid == -1)
    {
        printf("Клиент: ошибка при выполнении %s\n","shmid = shmget(shmkey, SIZEOFSHMSEG, 0666);");
        return -1;
    }

    /*Прикрепление сегмента разделяемой памяти, получение адреса*/
    shm_address = shmat(shmid, NULL, 0);
    if ( shm_address==NULL )
    {
        printf("Клиент: ошибка при выполнении %s\n","shm_address = shmat(shmid, NULL, 0);");
        return -1;
    }

    char str[BUFSIZ];


    while(1){
//        00 Сервер ожидает подключения клиента
//        01 Сервер ожидает передачи данных клиентом
//        10 Сообщение клиента готово для прочтения сервером
//        11 Данные ответа сервера клиенту готовы
// 3 бит 1 - работа сервера 0 - работа клиента

        operations[0].sem_num = 0;
        operations[0].sem_op =  0;
        operations[0].sem_flg = 0;

        operations[1].sem_num = 1;
        operations[1].sem_op =  0;
        operations[1].sem_flg = 0;

        operations[2].sem_num = 1;
        operations[2].sem_op =  1;
        operations[2].sem_flg = 0;

        operations[3].sem_num = 2;
        operations[3].sem_op =  1;
        operations[3].sem_flg = 0;

        scanf("%s", str);

        if (semop( semid, operations, 4 ) == -1)
        {
            printf("Клиент: ошибка при выполнении %s\n","semop( semid, operations, 2 ) == -1.");
            return -1;
        }
//        printf("%d %d\n", operations[0].sem_op, operations[1].sem_op);


        snprintf( (char *) shm_address, SIZEOFSHMSEG, "%s", str );
        usleep(200);

        operations[0].sem_num = 0;
        operations[0].sem_op =  -1;
        operations[0].sem_flg = 0;

        operations[1].sem_num = 1;
        operations[1].sem_op =  -1;
        operations[1].sem_flg = 0;

        operations[2].sem_num = 2;
        operations[2].sem_op =  0;
        operations[2].sem_flg = 0;


        if (semop( semid, operations, 3 ) == -1) // ждет 01 есть 10 сообщение в буфере
        {
            printf("Клиент: ошибка при изменении семафоров: %s\n","semop( semid, operations, 2 ) == -1.");
            return -1;
        }
//        printf("%d %d\n", operations[0].sem_op, operations[1].sem_op);

        printf("%s", (char *) shm_address);

        if (strcmp(str, "STOP") == 0) break;
    }  /* Конец цикла отправки сообщений */

    /*Открепление сегмента разделяемой памяти.*/
    if (shmdt(shm_address) == -1)
    {
        printf("Клиент: ошибка при откреплении сегмента разделяемой памяти: %s\n","shmdt(shm_address) == -1.");
        return -1;
    }

    return 0;
}