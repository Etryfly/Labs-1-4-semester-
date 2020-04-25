#include <vector>
#include "Message.h"

#ifndef INC_2_AVLTREE_H
#define INC_2_AVLTREE_H

template <class Key>
class AVLTreeNode {
private:

    int height;


public:
    AVLTreeNode(Key k) {
        key = new Key(k);
        left=right=nullptr;
        height = 1;
    }


    int getHeight() {
        return this ? height : 0;
    }

    int getBFactor() {
        return right->getHeight()-left->getHeight();
    }

    void fixHeight() {
        int h1 = left->getHeight();
        int h2 = right->getHeight();
        if (h1>h2) {
            height = h1 + 1;
        } else {
            height = h2 + 1;
        }
    }

    AVLTreeNode* rotateRight()
    {
        AVLTreeNode* q = this->left;
        this->left = q->right;
        q->right = this;
        fixHeight();
        q->fixHeight();
        return q;
    }

    AVLTreeNode* rotateleft() {
        AVLTreeNode* p = this->right;
        this->right = p->left;
        p->left = this;
        fixHeight();
        p->fixHeight();
        return p;
    }

    AVLTreeNode* balance(){
        fixHeight();
        if( getBFactor()==2 ){
            if( right->getBFactor() < 0 )
                this->right = right->rotateRight();
            return rotateleft();
        }

        if( getBFactor()==-2 ){
            if( left->getBFactor() > 0  )
                this->left = left->rotateleft();
            return rotateRight();
        }
        return this; // балансировка не нужна
    }

    AVLTreeNode* findMin(AVLTreeNode* p){
        return p->left?findMin(p->left):p;
    }

    AVLTreeNode* removeMin(AVLTreeNode* p) {
        if( p->left==nullptr )
            return p->right;
        p->left = removeMin(p->left);
        return p->balance();
    }


    Key* key;
    AVLTreeNode* left;
    AVLTreeNode* right;
};


class AVLTree {
private:
    AVLTreeNode<Message>* root;

    AVLTreeNode<Message>* ins(AVLTreeNode<Message>* p, Message k)
    {
        if( !p ) {
            p = new AVLTreeNode<Message>(k);

            return p;
        }

        if( k<*p->key )
            p->left = ins(p->left,k);
        else
            p->right = ins(p->right,k);
        return p->balance();

    }

    AVLTreeNode<Message>* rm(AVLTreeNode<Message>* p, Message k) // удаление ключа k из дерева p
    {
        if( !p ) return nullptr;
        if( k < *p->key )
            p->left = rm(p->left,k);
        else if( k > *p->key )
            p->right = rm(p->right,k);
        else //  k == p->key
        {
            AVLTreeNode<Message>* q = p->left;
            AVLTreeNode<Message>* r = p->right;
            delete p;
            if( !r ) return q;
            AVLTreeNode<Message>* min = r->findMin(r);
            min->right = r->removeMin(r);
            min->left = q;
            return min->balance();
        }
        return p->balance();
    }

public:

    AVLTree() {
        root = nullptr;
    }


    AVLTreeNode<Message>* insert(Message k) {
        auto node = ins(root, k);
        if (!root ) root = node;
        return node;
    }


    AVLTreeNode<Message>* remove( Message k) {
        return rm(root, k);
    }

    AVLTreeNode<Message>* getRoot() {
        return root;
    }

    void getMessagesByName(AVLTreeNode<Message> *p, std::string name, std::vector<Message> v) {

        if (!p) return;

        if (p->key->name == name) {
            v.push_back(*p->key);
        }

        if (p->key->name == name) {
            getMessagesByName(p->right, name, v);
        }
        if (p->key->name == name) {
            getMessagesByName(p->left, name, v);
        }

    }

};

#endif //INC_2_AVLTREE_H
