#ifndef AVL_H
#define AVL_H

#include <queue>
#include <iostream>
using namespace std;

typedef struct Node* nodeptr;

struct Node {
    int height;
    int key;

    nodeptr data;
    Node* leftChild;
    Node* rightChild;
};

class bstree {
public:
    Node* insert(const int value, Node*& root);
    void show(Node* root) ;
    void search(const int key, Node* root);
    Node* del(const int key, Node* root);
};

#endif