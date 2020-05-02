#include <vector>
#include "Message.h"

#ifndef INC_2_AVLTREE_H
#define INC_2_AVLTREE_H

class AVLTreeNode {
public:
    Message *key;
    int height;
    AVLTreeNode *left;
    AVLTreeNode *right;

    AVLTreeNode(Message k) {
        left = right = 0;
        height = 1;
        key = new Message(k);
    }


    int getHeight(AVLTreeNode *N) {
        if (N == NULL)
            return 0;
        return N->height;
    }

    int getBalance(AVLTreeNode *N) {
        if (N == NULL)
            return 0;
        return getHeight(N->left) - getHeight(N->right);
    }


    int max(int a, int b) {
        return (a > b) ? a : b;
    }


    AVLTreeNode *leftRotate(AVLTreeNode *root) {
        AVLTreeNode *x = root->right;
        AVLTreeNode *t = x->left;

        root->right = t;
        x->left = root;


        x = updateHeight(x);
        root = updateHeight(root);

        return x;
    }

    AVLTreeNode *rightRotate(AVLTreeNode *root) {
        AVLTreeNode *x = root->left;
        AVLTreeNode *t = x->right;

        root->left = t;
        x->right = root;


        root = updateHeight(root);
        x = updateHeight(x);

        return x;
    }

    AVLTreeNode *updateHeight(AVLTreeNode *node) {
        node->height = 1 + max(getHeight(node->left), getHeight(node->right));
        return node;
    }

    AVLTreeNode *insert(AVLTreeNode *root, Message value) {
        if (root == nullptr)
            return new AVLTreeNode(value);

        if (*root->key < value)
            root->right = insert(root->right, value);
        else if (*root->key == value) {

            return root;
        } else
            root->left = insert(root->left, value);

        root = updateHeight(root);

        int balance_factor = getHeight(root->left) - getHeight(root->right);


        if (balance_factor > 1 && *root->left->key < value) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        } else if (balance_factor > 1 && *root->left->key > value)
            return rightRotate(root);

        else if (balance_factor < -1 && *root->right->key < value)
            return leftRotate(root);

        else if (balance_factor < -1 && *root->right->key > value) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    AVLTreeNode *findmin(AVLTreeNode *p) {
        return p->left ? findmin(p->left) : p;
    }


    void getMessagesByName(AVLTreeNode *p, std::string name, std::vector<Message> *v) {

        if (!p) return;

        if (p->key->name == name) {
            v->push_back(*p->key);
        }

        if (p->right && p->right->key->name >= name) {
            getMessagesByName(p->right, name, v);
        }
        if (p->left && p->left->key->name <= name) {
            getMessagesByName(p->left, name, v);
        }

    }

    void getMessagesByUserInInterval(AVLTreeNode *p, boost::posix_time::ptime time1, boost::posix_time::ptime time2,
                                     std::string name, std::vector<Message> *v) {
        if (!p) return;

        if (p->key->time > time1 && p->key->time < time2 && name == p->key->name) {
            v->push_back(*p->key);
        }

        if (p->right && p->right->key->name >= name) {
            getMessagesByUserInInterval(p->right, time1, time2, name, v);
        }

        if (p->left && p->left->key->name <= name) {
            getMessagesByUserInInterval(p->left, time1, time2, name, v);
        }

    }

    void getMessagesInInterval(AVLTreeNode *p, boost::posix_time::ptime time1, boost::posix_time::ptime time2,
                               std::vector<Message> *v) {
        if (!p) return;

        if (p->key->time > time1 && p->key->time < time2) {
            v->push_back(*p->key);
        }

        if (p->right) {
            getMessagesInInterval(p->right, time1, time2, v);
        }

        if (p->left) {
            getMessagesInInterval(p->left, time1, time2, v);
        }

    }
};

#endif //INC_2_AVLTREE_H
