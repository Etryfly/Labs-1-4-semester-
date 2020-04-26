#include <vector>
#include "Message.h"

#ifndef INC_2_AVLTREE_H
#define INC_2_AVLTREE_H
class AVLTreeNode {
public:
    Message* key;
    unsigned char height;
    AVLTreeNode* left;
    AVLTreeNode* right;
    AVLTreeNode(Message k) {
        left = right = 0;
        height = 1;
        key = new Message(k);
    }


unsigned char getHeight(AVLTreeNode* p)
{
    return p?p->height:0;
}

int bfactor(AVLTreeNode* p)
{
    return getHeight(p->right)-getHeight(p->left);
}

void fixheight(AVLTreeNode* p)
{
    unsigned char hl = getHeight(p->left);
    unsigned char hr = getHeight(p->right);
    p->height = (hl>hr?hl:hr)+1;
}

AVLTreeNode* rotateright(AVLTreeNode* p) // правый поворот вокруг p
{
    AVLTreeNode* q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

AVLTreeNode* rotateleft(AVLTreeNode* q) // левый поворот вокруг q
{
    AVLTreeNode* p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

AVLTreeNode* balance(AVLTreeNode* p) // балансировка узла p
{
    fixheight(p);
    if( bfactor(p)==2 )
    {
        if( bfactor(p->right) < 0 )
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if( bfactor(p)==-2 )
    {
        if( bfactor(p->left) > 0  )
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

AVLTreeNode* insert(AVLTreeNode* p, Message k) // вставка ключа k в дерево с корнем p
{
    if( !p ) return new AVLTreeNode(k);
    if( k<*p->key )
        p->left = insert(p->left,k);
    else
        p->right = insert(p->right,k);
    return balance(p);
}

AVLTreeNode* findmin(AVLTreeNode* p) // поиск узла с минимальным ключом в дереве p
{
    return p->left?findmin(p->left):p;
}

AVLTreeNode* removemin(AVLTreeNode* p) // удаление узла с минимальным ключом из дерева p
{
    if( p->left==0 )
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

AVLTreeNode* remove(AVLTreeNode* p, Message *k) // удаление ключа k из дерева p
{
    if( !p ) return 0;
    if( k < p->key )
        p->left = remove(p->left,k);
    else if( k > p->key )
        p->right = remove(p->right,k);
    else //  k == p->key
    {
        AVLTreeNode* q = p->left;
        AVLTreeNode* r = p->right;
        delete p;
        if( !r ) return q;
        AVLTreeNode* min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
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

        if (p->left  && p->left->key->name <= name) {
            getMessagesByUserInInterval(p->left, time1, time2, name, v);
        }

    }

    void getMessagesInInterval(AVLTreeNode *p, boost::posix_time::ptime time1, boost::posix_time::ptime time2,
                                     std::vector<Message> *v) {
        if (!p) return;

        if (p->key->time > time1 && p->key->time < time2) {
            v->push_back(*p->key);
        }

        if (p->right ) {
            getMessagesInInterval(p->right, time1, time2, v);
        }

        if (p->left  ) {
            getMessagesInInterval(p->left, time1, time2, v);
        }

    }
};
#endif //INC_2_AVLTREE_H
