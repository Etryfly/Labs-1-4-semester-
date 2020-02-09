#include "sort.h"
#include "udt.h"

int main() {
    Udt* list = udtCreate();
    int action = -100;

    while (action != 7) {
        scanf("%d", &action);

        switch (action) {
            //добавление элемента в список
            case 1: {

                int key = 0;
                scanf("%d",&key);
                int d = 0;
                scanf("%d",&d);
                int data = d;
                Item* item = createNewItem(key, data);
                udtInsert(list, udtSize(list), item);


                break;
            }

            case 2:
                udtPrint(list);
                break;

            case 3: {
                int pos = 0;
                scanf("%d", &pos);
                listRemove(list,pos);
                break;
            }

            case 4:
                printf("%d", udtSize(list));
                break;

            case 5:
                search(list);
                break;

            case 6:
                sort(list);
        }
    }

}