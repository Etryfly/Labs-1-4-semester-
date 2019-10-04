// 1 2 + 3 *    = 9

#include <stdlib.h>
#include <stdio.h>

typedef struct _item {
    struct _item* prev;
    char data;
} Item;

typedef struct _stack {
    Item* top;
    int size;
} Stack;

void pop(Stack* stack);
Item* top(Stack* stack);

void push(Stack* stack, char data);
Stack* createStack();

char action(char action, int l, int r) {
    switch (action) {
        case '+':
            return (char) (l + r + '0');

        case '*':
            return (char) (l * r + '0');

        case '-':
            return (char) (l - r + + '0');

        case '/':
            return (char) (l / r + '0');
    }

    return 0;

}

int main() {
    Stack* stack = createStack();
    int n;
    scanf("%d",&n);
    for (int i = 0; i < n; ++i) {
        char data;
        scanf("%c", &data);
        if (data == '\n' || data == ' ') {
            i--;
            continue;
        }

        if (data >= '0' && data <= '9') {
            push(stack, data);
        } else {
            int l =  top(stack)->data - '0';
            pop(stack);
            int r = (int) top(stack)->data - '0';
            pop(stack);
            push(stack, action(data, l, r));
        }
    }

    for (int j = 0; j < stack->size; ++j) {
        printf("%d ", top(stack)->data - '0');
        pop(stack);
    }

}



void pop(Stack* stack) {
    if (stack->size > 0) {
        Item *prev = stack->top;
        stack->top = stack->top->prev;
        stack->size--;
        free(prev);
    } else {
        printf("Стек пуст");
    }
}

Item* top(Stack* stack) {
    return stack->top;
}

void push(Stack *stack, char data) {
    Item* item = malloc(sizeof(Item));
    item->prev = stack->top;
    item->data = data;
    stack->top = item;
    stack->size++;
}

Stack* createStack() {
    Stack* stack = malloc(sizeof(Stack));
    stack->size = 0;
    stack->top=0;
    return stack;
}