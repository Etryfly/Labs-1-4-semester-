
#ifndef UDT_H
#define UDT_H

#include <stdio.h>
#include <stdlib.h>

typedef struct _Item
{
	int key;
	int data;
	struct _Item* next;
} Item;

typedef Item UDT_TYPE;

typedef struct _Udt
{
	Item* begin;
} Udt;

void listRemove(Udt* list, int pos);
Udt* udtCreate();
int udtSize(Udt *udt);
Item* createNewItem(int key, int data);
int udtEmpty(const Udt *udt);
void udtPush(Udt *udt, const UDT_TYPE value);
UDT_TYPE udtFront(const Udt *udt);
void udtPop(Udt *udt);
void udtPrint(Udt *udt);
void udtDestroy(Udt *udt);
void udtInsert(Udt *udt, int pos, Item* item);
void search(Udt* udt);
#endif