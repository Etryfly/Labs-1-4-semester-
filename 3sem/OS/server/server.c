#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"

void sys_err (char * msg)
{
    puts (msg);
    exit (1);
};

int fact(int N) {
    if (N < 0)
        return 0;
    if (N == 0)
        return 1;
    else
        return N * fact(N - 1);
}

int comb(int a, int b) {
    return fact(b)/fact(a)*fact(b-a);
}
int main ()
{
    int msqid;
    message_t msg;

    /* создание очереди сообщений */
    if ( (msqid = msgget (MSQ_ID, PERMS | IPC_CREAT) ) < 0)
        sys_err ("server: can not create msg queue");

    while (1) {
        /* получение очередного сообщения */
        if (msgrcv (msqid, &msg, sizeof (message_t), 0, 0) < 0)
            sys_err ("server: msg recive error");

        if (msg.type == AB) {/* печать строки */
            int result = comb(msg.a, msg.b);
            msg.result = result;
            msg.type = RESULT;
            msgsnd (msqid, &msg, sizeof (message_t), 0);
        }

        if (msg.type == MSG_TYPE_FINISH) /* выход из цикла */
            break;
    }

    /* удаление очереди сообщений */
    if (msgctl (msqid, IPC_RMID, (struct msqid_ds *) 0) < 0)
        sys_err ("server: msq queue remove error");

    exit (0);
}