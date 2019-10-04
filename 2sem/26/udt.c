
#include <stdlib.h>
#include <stdio.h>
#include "udt.h"
#define Therminator -1

typedef struct _iterator {
    Item* curr;
} Iterator;




Item* createNewItem(int key, int data) {
    Item* item = (Item*)malloc(sizeof(Item));
    item->data = data;
    item->key = key;
    return item;
}

Udt* udtCreate() {
    Udt *list = (Udt *)malloc(sizeof(Udt));
    list->begin = createNewItem(Therminator, Therminator);
    return list;
}



Iterator* getIterator(Udt *list) {
    Iterator *iterator = malloc(sizeof(Iterator));
    if (iterator == NULL) {
        printf("Ошибка при выделении памяти");
        return NULL;
    }
    iterator->curr = list->begin;
    return iterator;
}



void itNext(Iterator *iterator) {
    iterator->curr = iterator->curr->next;
}



Item* getNewTerminator() {
    Item* item = createNewItem(Therminator, Therminator);
    return item;
}

void udtInsert(Udt *list, int position, Item *item) {//вставка после pos
    Iterator* iterator = getIterator(list);
    for (int i = 0; i < position; ++i) {
        if (iterator->curr->data == Therminator) break;
        itNext(iterator);
    }
    if (iterator->curr->data != Therminator) {
        Item *afterInsert = iterator->curr->next;

        item->next = afterInsert;
        iterator->curr->next = item;

    } else {
        *iterator->curr = *item;
    }

    if (iterator->curr->next == NULL) iterator->curr->next = getNewTerminator();
    printf("Элемент %d добавлен\n",item->data);
}

Item* get(Udt* udt, int pos) {
    Iterator* iterator = getIterator(udt);
    for (int i = 0; i < pos; ++i) {
        itNext(iterator);
    }
    return iterator->curr;
}

void udtPrint(Udt *list) {
    Iterator* iterator = getIterator(list);
    while (iterator->curr->data!= Therminator) {
        printf("%d %d \n",  iterator->curr->key, iterator->curr->data);
        itNext(iterator);
    }
}

void listRemove(Udt* list, int pos) {
    Iterator* iterator = getIterator(list);
    Item* prev = iterator->curr;
    for (int i = 0; i < pos - 1; ++i) {
        if (iterator->curr->data == Therminator) {
            printf("Выход за границы списка");
            return;
        }
        prev=iterator->curr;
        itNext(iterator);
    }

    if (pos == 1) {
        list->begin = iterator->curr->next;
        free(prev);
    } else {

        prev->next = iterator->curr->next;
        free(iterator->curr);
    }

}

int udtSize(Udt *list) {
    Iterator* it = getIterator(list);
    int l = 0;
    while (it->curr->data != Therminator) {
        l ++;
        itNext(it);
    }
    return l;
}

int udtEmpty(const Udt *udt) {
    return (udt->begin->key==Therminator && udt->begin->data == Therminator ? 1: 0);
}

void udtPush(Udt *udt, const UDT_TYPE value) {
    udtInsert(udt, udtSize(udt), createNewItem(value.key,value.data));

}

void udtDestroy(Udt *udt) {
    while (udt->begin->next->data != Therminator) {
        listRemove(udt, 0);
    }
    udt->begin->data = Therminator;
    udt->begin->key = Therminator;
    udt->begin->next = getNewTerminator();

}

void search(Udt* udt) {
    for (int i = 1; i < udtSize(udt); ++i) {
        if (get(udt, i-1)->data>get(udt, i)->data) {
            Item* prev = get(udt, i-1);
            Item* curr = get(udt, i);
            prev->next = curr->next;
            curr->next = prev;
            if (i > 1)
                get(udt, i-2)->next=curr;
            else
                udt->begin = curr;

            break;
        }
    }
}
