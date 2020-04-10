//
// Created by etryfly on 28.03.2020.
//

#ifndef INC_2_RBTREE_H
#define INC_2_RBTREE_H
#define RED true
#define BLACK false


template <class T>
class RBTree {
private:
    RBTree * root;
    RBTree * right;
    RBTree * left;
    RBTree * parent;
    T* data;
    bool color;

    RBTree(T d) {
        color = RED;
        left = nullptr;
        right = nullptr;
        data = d;
        parent = nullptr;
    }

    void leftRotate() {
        RBTree* root = this;
        RBTree<T> *tmp = root->left;
        root->left = tmp->right;
        if (tmp->right != nullptr) {
            tmp->right->parent = root;
        }
        tmp->parent = root->parent;
        if (root == root->parent->left)
            root->parent->left = tmp;
        else
            root->parent->right = tmp;
        tmp->right = root;
        root->parent = tmp;
    }

    void rightRotate() {
        RBTree* root = this;
        RBTree<T> *tmp = root->right;
        root->right = tmp->left;
        if (tmp->left != nullptr) {
            tmp->left->parent = root;
        }
        tmp->parent = root->parent;
        if (root == root->parent->left)
            root->parent->left = tmp;
        else
            root->parent->right = tmp;
        tmp->left = root;
        root->parent = tmp;
    }

    void fixup() {
        while (this->parent != nullptr && this->parent->color == RED) {
            if (this->parent == this->parent->parent->left) {
                RBTree* uncle = this->parent->parent->right;
                if (uncle->color == RED) {
                    this->parent->color = BLACK;
                    uncle->color = BLACK;
                    this->parent->parent->color = RED;
                    this = this->parent->parent;
                } else {
                    if (this == this->parent->right) {
                        this = this->parent;
                        leftRotate(this);
                    }
                    this->parent->color = BLACK;
                    this->parent->parent->color = RED;
                    rightRotate(this->parent->parent);
                }
            } else {
                RBTree* uncle = this->parent->parent->left;
                if (uncle->color == RED) {
                    this->parent->color = BLACK;
                    uncle->color = BLACK;
                    this->parent->parent->color = RED;
                    this = this->parent->parent;
                } else {
                    if (this == this->parent->left) {
                        this = this->parent;
                        rightRotate(this);
                    }
                    this->parent->color = BLACK;
                    this->parent->parent->color = RED;
                    leftRotate(this->parent->parent);
                }
            }
        }
        this->color = BLACK;
    }





    void deleteFixup(RBTree *x) {

        /*************************************
         *  maintain Red-Black tree balance  *
         *  after deleting node x            *
         *************************************/

        while (x != root && x->color == BLACK) {
            if (x == x->parent->left) {
                RBTree *w = x->parent->right;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateLeft (x->parent);
                    w = x->parent->right;
                }
                if (w->left->color == BLACK && w->right->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->right->color == BLACK) {
                        w->left->color = BLACK;
                        w->color = RED;
                        rotateRight (w);
                        w = x->parent->right;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->right->color = BLACK;
                    rotateLeft (x->parent);
                    x = root;
                }
            } else {
                RBTree *w = x->parent->left;
                if (w->color == RED) {
                    w->color = BLACK;
                    x->parent->color = RED;
                    rotateRight (x->parent);
                    w = x->parent->left;
                }
                if (w->right->color == BLACK && w->left->color == BLACK) {
                    w->color = RED;
                    x = x->parent;
                } else {
                    if (w->left->color == BLACK) {
                        w->right->color = BLACK;
                        w->color = RED;
                        rotateLeft (w);
                        w = x->parent->left;
                    }
                    w->color = x->parent->color;
                    x->parent->color = BLACK;
                    w->left->color = BLACK;
                    rotateRight (x->parent);
                    x = root;
                }
            }
        }
        x->color = BLACK;
    }

public:
    RBTree add(T d) {
        if (root == nullptr) {
            root = new RBTree(d);
            root->color = BLACK;
            root->parent = nullptr;
        } else {
            RBTree* node;
            RBTree* parent;
            for (node = root; node != nullptr; ) {
                parent = node;
                if (d < node->data) {
                    node = node->left;
                } else if (d > node->data) {
                    node = node->right;
                } else {
                    return root;
                }

            }

            node = new RBTree(d);
            node->parent = parent;
            node->root = root;

            if (parent != nullptr) {
                if (d < parent->data) {
                    parent->left = node;
                } else {
                    parent->right = node;
                }
            } else {
                root = node;
            }
        }

        fixup();
        return root;
    }

    void deleteNode(RBTree *z) {
        RBTree *x, *y;

        /*****************************
         *  delete node z from tree  *
         *****************************/

        if (!z || z == nullptr) return;


        if (z->left == nullptr || z->right == nullptr) {
            /* y has a nullptr node as a child */
            y = z;
        } else {
            /* find tree successor with a nullptr node as a child */
            y = z->right;
            while (y->left != nullptr) y = y->left;
        }

        /* x is y's only child */
        if (y->left != nullptr)
            x = y->left;
        else
            x = y->right;

        /* remove y from the parent chain */
        x->parent = y->parent;
        if (y->parent)
            if (y == y->parent->left)
                y->parent->left = x;
            else
                y->parent->right = x;
        else
            root = x;

        if (y != z) z->data = y->data;


        if (y->color == BLACK)
            deleteFixup (x);

        free (y);
    }

    RBTree *findNode(T data) {

        /*******************************
         *  find node containing data  *
         *******************************/

        RBTree *current = root;
        while(current != nullptr)
            if(compEQ(data, current->data))
                return (current);
            else
                current = compLT (data, current->data) ?
                          current->left : current->right;
        return(0);
    }
};




#endif //INC_2_RBTREE_H
