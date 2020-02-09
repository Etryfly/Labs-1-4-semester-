#include <stdio.h>

typedef struct _node {
    struct _node *left;
    struct _node *right;
    struct _node *parent;
} Node;

int depth(int max, Node* curr) {
    if (curr != NULL) {
        max++;
        if (curr->right) depth(max,curr->right);
        if (curr->left) depth(max,curr->left);
    }
}

int main() {
    Node* root;
    /*
     *
     * Построение дерева
     */
    printf("%d", depth(root,0));
}