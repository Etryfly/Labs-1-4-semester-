/* Вариант 12 Проверить, является ли двоичное дерево линейным списком вершин
+ добавление ноды (например rlrr 13)
- удаление ноды (rlrr по элементу)
d удаление ноды (13 по значению)
p вывод дерева
! функция из задания

*/
#include "string.h"
#include <stdlib.h>
#include "stdio.h"



typedef struct tree {
    int data;
    struct tree *left;
    struct tree *right;
    struct tree *parent;
} Tree;

Tree* search_leaf(Tree* root);

void delete_tree(Tree *pTree);

static Tree *root;



void print_node(Tree *a) {
    if ( a == NULL) {

    } else {//Для дебага
//Для дебага
//        if (a->parent) printf("p%d ", a->parent->data);
//        if (a->left) printf("l%d ",a->left->data);
//        if (a->right) printf("r%d ",a->right->data);



        printf("%d",a->data);
    }
}

void print_space(int span) {
    for (int i = 0; i < span; ++i) {
        printf(" ");
    }
}

void print_all_tree(Tree* cur, int span) {
    print_space(span);
    print_node(cur);
    printf("\n");
   if (cur) {
       if (cur->right) {
           print_all_tree(cur->right,span+5);
            span-=5;
       }
       if (cur->left) {
           print_all_tree(cur->left,span+3);
           span-=2;
       }
   }
}

Tree* create_left_node(Tree *parent,int data) {
    parent->left=(Tree *)calloc(1,sizeof(Tree));
  //  if (!parent->left) return parent;
    parent->left->data=data;
    parent->left->parent=parent;

    parent->left->right=NULL;
    parent->left->left=NULL;
    return parent->left;
}

Tree* create_right_node(Tree *parent,int data) {
    parent->right=(Tree *)calloc(1,sizeof(Tree));
    //if (parent->right==NULL) return parent;
    parent->right->data=data;
    parent->right->parent=parent;
    parent->right->left=NULL;
    parent->right->right=NULL;
    return parent->right;
}

int check_line(Tree* root) {//проверяет, является ли дерево линейным списком
    Tree* cur = root;
    if (!root) return 0;
    while (cur->right || cur->left) {
        if (cur->right && !cur->left) {
            cur=cur->right;
        }
        if (cur->left && !cur->right) {
            cur=cur->left;
        }
        if (cur->left && cur->right) return 0;
    }
    return 1;


}

Tree* add(Tree* cur, char prev_char) {

    char c = getchar();
    switch (c) {
        case 'r': {
            if (cur->right) {
                add(cur->right, 'p');
            } else {
                add(cur, 'r');
            }
            break;
        }

        case 'l': {
            if (cur->left) {
                add(cur->left, 'p');
            } else {
                add(cur,'l');
            }
            break;
        }

        default: {
            int a = c-'0';
            int tmp = getchar();
            while (tmp != '\n') {
                a = a * 10 + (tmp - '0');
                tmp=getchar();
            }



            if (prev_char == 'l') return create_left_node(cur, a);
            if (prev_char == 'r') return create_right_node(cur, a);

        }
    }
}

void delete_root(Tree* r) {
    if (r->right && !r->left) {
        root = r->right;


    } else if (r->left && !r->right) {
            root = r->left;

        } else if (!r->left && !r->right) {
        free(root->parent);
        root->parent=NULL;
        free(root);
        root = NULL;
            } else if (r->right && r->left) {
                Tree* leaf_under = search_leaf(r);
                free(leaf_under->parent);
                leaf_under->parent=NULL;
                if (r->right!=leaf_under) leaf_under->right=r->right;
                if (r->left!=leaf_under) leaf_under->left=r->left;

                if (leaf_under->right) leaf_under->right->parent=leaf_under;
                if (leaf_under->left) leaf_under->left->parent=leaf_under;
                root=leaf_under;
    }

    if (root && root->parent) {
        free(root->parent);
        root->parent=NULL;
    }

}

void delete(Tree *cur) {
    if (cur->parent == NULL) {
       delete_root(root);

    } else {

        if (cur->right && !cur->left) {
            if (cur->parent->right == cur) {
                cur->parent->right = cur->right;
                cur->right->parent = cur->parent;
            } else {
                cur->parent->left = cur->right;
                cur->right->parent = cur->parent;
            }
            free(cur);
        }
        if (cur->left && !cur->right) {
            if (cur->parent->right == cur) {
                cur->parent->right = cur->left;
                cur->left->parent = cur->parent;
            } else {
                cur->parent->left = cur->left;
                cur->left->parent = cur->parent;
            }
            free(cur);
        }

        if (!cur->left && !cur->right) {
            if (cur->parent->right == cur) {
                cur->parent->right = NULL;
            }
            if (cur->parent->left == cur) {
                cur->parent->left = NULL;
            }

            free(cur);
        }

        if (cur->right && cur->left) {
            Tree *leaf_under = search_leaf(cur);
            leaf_under->parent = cur->parent;
            if (cur->right != leaf_under) leaf_under->right = cur->right;
            if (cur->left != leaf_under) leaf_under->left = cur->left;


            if (cur->parent->right == cur) {
                cur->parent->right = leaf_under;
            }
            if (cur->parent->left == cur) cur->parent->left = leaf_under;
            if (leaf_under->right) leaf_under->right->parent = leaf_under;
            if (leaf_under->left) leaf_under->left->parent = leaf_under;

            free(cur);
        }
    }
}

Tree* minus(Tree* cur) {//удаляет по пути rlrl
    char c = getchar();
    switch (c) {
        case 'r': {
            if (cur->right) {
                minus(cur->right);
            }
            break;
        }

        case 'l': {
            if (cur->left) {
                minus(cur->left);
            }
            break;
        }

        default:
            delete(cur);
            //удаление cur ноды
    }

}



Tree *search_leaf(Tree *root) {
    while (root->right || root->left) {
        if (root->right) root = root->right;
        if (root->left) root = root->left;
    }
    return root;
}

Tree* d(Tree *cur, int a) {//удаляет по значению
    if (cur->data!=a) {
        if (cur->left) d(cur->left,a);
        if (cur->right) d(cur->right,a);
    } else {
       delete(cur);
    }
}
static int MAX = 0;

void depth(int max, Tree* curr) {
    if (curr != NULL) {
        max++;
        if (MAX < max) {
            MAX = max;
        }
        if (curr->right) depth(max,curr->right);
        if (curr->left) depth(max,curr->left);
    }

}

Tree* exc(Tree* cur) {

    int c;
    while (c = getchar() ) {
        switch (c) {
            case '+':
                if (!root) {
                    root=(Tree *)malloc(sizeof(Tree));
                    int a = 0;
                    int tmp = getchar();
                    while (tmp != '\n') {
                        if (tmp != 'r' && tmp != 'l') {
                            a = a * 10 + (tmp - '0');
                        }
                        tmp=getchar();
                    }
                    root->data = a;
                    root->parent=NULL;
                    break;
                }else {
                    add(root, 0);
                }
               break;

            case 'p':
                print_all_tree(root, 50);
                break;

            case 'd': {
                int a = 0;
                int tmp = getchar();
                while (tmp != '\n') {
                    a = a * 10 + (tmp - '0');
                    tmp = getchar();
                }
                    d(root, a);

                break;
            }

            case '!':
                if (check_line(root)) printf("LIN\n"); else printf("NO\n");
                break;

            case '-':
                minus(root);

            case 'b':
               // printf("DELETE");
               if (root) delete_tree(root);
                return NULL;
                break;

            case 'l':
                MAX = 0;
                depth(0, root);
                printf("%d", MAX);

                break;
        }
    }
    //printf("DELETE");

    delete_tree(root);
    if (root) delete_tree(root);

}


void delete_tree(Tree *cur) {
    if (cur->right) delete_tree(cur->right);
    if (cur->left) delete_tree(cur->left);
    cur->right=NULL;
    cur->left=NULL;
    cur->parent=NULL;
    cur->data=0;
    free(cur);
}



int main() {
    root = NULL;
   exc(root);


}



