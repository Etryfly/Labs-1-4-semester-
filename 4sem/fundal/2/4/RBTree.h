//
// Created by etryfly on 28.03.2020.
//

#ifndef INC_2_RBTREE_H
#define INC_2_RBTREE_H
#define RED true
#define BLACK false


template <class Key, class Data>
class RBTree {
private:

    RBTree * right;
    RBTree * left;
    RBTree * parent;
    Key* key;
    Data* data;

    bool color;





    void leftRotate(RBTree* node) {
        RBTree* root = node;
        RBTree<Key, Data> *tmp = root->left;
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

    void rightRotate(RBTree* node) {
        RBTree* root = node;
        RBTree<Key, Data> *tmp = root->right;
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

    void fixup(RBTree* node) {
        while (node->parent != nullptr && node->parent->color == RED) {
            if (node->parent == node->parent->parent->left) {
                RBTree* uncle = node->parent->parent->right;
                if (uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        leftRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    rightRotate(node->parent->parent);
                }
            } else {
                RBTree* uncle = node->parent->parent->left;
                if (uncle->color == RED) {
                    node->parent->color = BLACK;
                    uncle->color = BLACK;
                    node->parent->parent->color = RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rightRotate(node);
                    }
                    node->parent->color = BLACK;
                    node->parent->parent->color = RED;
                    leftRotate(node->parent->parent);
                }
            }
        }
        node->color = BLACK;
    }





    void deleteFixup(RBTree* z) {
        while(z->data != root->data && z->color == BLACK) {
            auto sibling = root;
            if(z->parent->left == z) {
                if(z->parent->right){ sibling = z->parent->right; }
                if(sibling) {
                    //CASE -- 1
                    if(sibling->color == RED) {
                        sibling->color = BLACK;
                        z->parent->color = RED;
                        leftRotate(z->parent);
                        sibling = z->parent->right;
                    }
                    //CASE -- 2
                    if(sibling->left == nullptr && sibling->right == nullptr) {
                        sibling->color = RED;
                        z = z->parent;
                    }
                    else if(sibling->left->color == BLACK && sibling->right->color == BLACK) {
                        sibling->color = RED;
                        z = z->parent;
                    }
                        //CASE -- 3
                    else if(sibling->right->color == BLACK) {
                        sibling->left->color = BLACK;
                        sibling->color = RED;
                        rightRotate(sibling);
                        sibling = z->parent->right;
                    } else {
                        sibling->color = z->parent->color;
                        z->parent->color = "BLACK";
                        if(sibling->right){ sibling->right->color = "BLACK"; }
                        leftRotate(z->parent);
                        z = root;
                    }
                }
            } else {
                if(z->parent->right == z){
                    if(z->parent->left){ sibling = z->parent->left; }
                    if(sibling) {
                        //CASE -- 1
                        if(sibling->color == RED){
                            sibling->color = BLACK;
                            z->parent->color = RED;
                            rightRotate(z->parent);
                            sibling = z->parent->left;
                        }
                        //CASE -- 2
                        if(sibling->left == nullptr && sibling->right == nullptr) {
                            sibling->color = RED;
                            z = z->parent;
                        }
                        else if(sibling->left->color == BLACK && sibling->right->color == BLACK) {
                            sibling->color = RED;
                            z = z->parent;
                        }
                            //CASE -- 3
                        else if(sibling->left->color == BLACK) {
                            sibling->right->color = BLACK;
                            sibling->color = RED;
                            rightRotate(sibling);
                            sibling = z->parent->left;
                        } else {
                            sibling->color = z->parent->color;
                            z->parent->color = BLACK;
                            if(sibling->left){ sibling->left->color = BLACK; }
                            leftRotate(z->parent);
                            z = root;
                        }
                    }
                }

            }
        }
        z->color = BLACK;
    }

public:

    RBTree * root;

    RBTree(Key k , Data* d) {
        color = RED;
        left = nullptr;
        right = nullptr;
        data = d;
        key = new std::string(k);
        parent = nullptr;
    }

    RBTree() {
        root = nullptr;
        right = nullptr;
        left = nullptr;
        data = nullptr;
        key = nullptr;
        parent = nullptr;
        color = BLACK;
    }

    RBTree *add(Key k, Data* d) {
        if (root == nullptr) {
            root = new RBTree(k, d);
            root->color = BLACK;
            root->parent = nullptr;
            root->root = root;
        } else {
            RBTree* node;
            RBTree* parent;
            for (node = root; node != nullptr; ) {
                parent = node;
                if (k < *node->key) {
                    node = node->left;
                } else if (k > *node->key) {
                    node = node->right;
                } else {
                    return root;
                }

            }

            node = new RBTree(k, d);
            node->parent = parent;
            node->root = root;

            if (parent != nullptr) {
                if (k < *parent->key) {
                    parent->left = node;
                } else {
                    parent->right = node;
                }
            } else {
                root = node;
            }
            node->root = node->parent->root;
            fixup(node);
        }


        return root;
    }

    void deleteNode(RBTree *z) {
        RBTree *x, *y;

        /*****************************
         *  delete node z from tree  *
         *****************************/

        if (!z || z == nullptr) return;


        if (z->left == nullptr || z->right == nullptr) {
            /* y has a nullptr AVLTreeNode as a child */
            y = z;
        } else {
            /* find tree successor with a nullptr AVLTreeNode as a child */
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

    RBTree *findNode(Key key) {

        /*******************************
         *  find node containing data  *
         *******************************/

        RBTree *current = root;
        while(current != nullptr)
            if(key == *current->key)
                return (current);
            else
                current = (key < *current->key) ?
                          current->left : current->right;
        return(0);
    }

    Data* getData() {
        return data;
    }

    void setData(Data* d) {
        data = d;
    }

    void printTree(RBTree* tree) {
        if (tree == nullptr) return;
        std::cout << *tree->data << std::endl;

        printTree(tree->left);
        printTree(tree->right);
    }

    void getAsVector(std::vector<RBTree*> *v, RBTree* root) {
        if (root == nullptr) return;
        v->push_back(root);
        getAsVector(v, root->left);
        getAsVector(v, root->right);
    }
};

#endif //INC_2_RBTREE_H
