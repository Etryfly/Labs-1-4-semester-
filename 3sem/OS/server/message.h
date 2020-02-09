#include <sys/types.h>
//#include <sys/ips.h>
#include <sys/msg.h>

#define MSQ_ID   2001     /* уникальный ключ очереди */
#define PERMS    00666    /* права доступа - все могут
                             читать и писать */
#define AB 1 /* тип сообщения о том, что */
#define RESULT 3 /* тип сообщения о том, что
                             передана непустая строка */
#define MSG_TYPE_FINISH 2 /* тип сообщения о том, что
                             пора завершать обмен */
                          
#define MAX_STRING 120    /* максимальная длина строки */
          
typedef struct            /* структура сообщения */
{
  int type;
  int a;
  int result;
  int b;
}
message_t;