#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "message.h"

void sys_err (char * msg)
{
    puts (msg);
    exit (1);
}

int main ()
{
    int msqid;      /* идентификатор очереди сообщений */
    message_t msg;  /* сообщение */
    int a,b;

    /* создание очереди */
    if ( (msqid = msgget (MSQ_ID, 0)) < 0)
        sys_err ("client:can not get msg queue");

    while (1) {
        scanf ("%d", &a); /* ввод строки */
        scanf ("%d", &b); /* ввод строки */
        if (! (a == 0 && b == 0)) {
            msg.type = AB;
            msg.a = a;
            msg.b = b;
        }
        else
        {
            msg.type = MSG_TYPE_FINISH;
        };
        /* посылка сообщения процессу-серверу */
        if (msgsnd (msqid, &msg, sizeof (message_t), 0) != 0) {
            sys_err("client: message send error");
        }

        if (msgrcv (msqid, &msg, sizeof (message_t), 0, 0) < 0)
            sys_err ("server: msg recive error");
        if (msg.type == RESULT) {
            printf("%d", msg.result);
        }

        if (a == 0 && b == 0) /* пустая строка - выход */
            break;
    }
    exit (0);
}