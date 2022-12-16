#include "AVL.h"

int getHeight(nodeptr r) {
    if (r == nullptr)
        return 0;
    else
        return r->height;
}

int getBalanceFactor(nodeptr r) {
    return getHeight(r->leftChild) - getHeight(r->rightChild);
}

nodeptr RotateLeft(nodeptr x) {
        nodeptr y = x->rightChild;
    x->rightChild = y->leftChild;
    y->leftChild = x;

    x->height = std::max(getHeight(x->leftChild), getHeight(x->rightChild)) + 1;
    y->height = std::max(getHeight(y->leftChild), getHeight(y->rightChild)) + 1;

    return y;
}

nodeptr RotateRight(nodeptr y) {
    nodeptr x = y->leftChild;
    y->leftChild = x->rightChild;
    x->rightChild = y;

    y->height = std::max(getHeight(y->leftChild), getHeight(y->rightChild)) + 1;
    x->height = std::max(getHeight(x->leftChild), getHeight(x->rightChild)) + 1;

    return x;
}

void Balancing(nodeptr &r, int item) {
    int bF = getBalanceFactor(r);

    // left left
    if (bF > 1 && getBalanceFactor(r->leftChild) >= 0) {
        r = RotateRight(r);
    }
    // left right
    else if (bF > 1 && getBalanceFactor(r->leftChild) < 0) {
        r->leftChild = RotateLeft(r->leftChild);
        r = RotateRight(r);
    }
    // right right
    else if (bF < -1 && getBalanceFactor(r->rightChild) <= 0) {
        r = RotateLeft(r);
    }
    // right left
    else if (bF < -1 && getBalanceFactor(r->rightChild) > 0) {
        r->rightChild = RotateRight(r->rightChild);
        r = RotateLeft(r);
    }
}

Node* bstree::insert(const int value, Node*& root) {
    if (root == nullptr) {
        nodeptr z = new Node;
        z->key = value;
        root = z;
        return root;
    } else if (root->key < value) {
        root->rightChild = insert(value, root->rightChild);
    } else {
        root->leftChild = insert(value, root->leftChild);
    }

    root->height = std::max(getHeight(root->leftChild), getHeight(root->rightChild)) + 1;

    Balancing(root, value);
    return root;
};

void bstree::show(Node* root) {
    if (root != nullptr) {
        std::cout << root->key << '\t';

        std::cout << "left : ";
        if (root->leftChild != nullptr)
            std::cout << root->leftChild->key << '\t';
        else std::cout << "empty" << '\t';;

        std::cout << "right : ";
        if (root->rightChild != nullptr)
            std::cout << root->rightChild->key << '\t';
        else std::cout << "empty" << '\t';

        std::cout << endl;
        show(root->leftChild);
        show(root->rightChild);
    }
};

void bstree::search(const int key, Node* root) {
    if (root == NULL)
        return;

    std::cout << root->key;

    if (root->key == key)
        return;

    // If the key is less than the current node, search the left subtree
    if (key < root->key) {
        std::cout << "->";
        search(key, root->leftChild);
    }
        
    // If the key is greater than the current node, search the right subtree
    else if (key > root->key) {
        std::cout << "->";
        search(key, root->rightChild);
    }
}

Node * minNode(Node* node) { 
    Node* current = node; 

    while (current->leftChild != NULL) 
        current = current->leftChild; 
    return current; 
} 

Node* bstree::del(const int key, Node* root) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        del(key, root->rightChild);

    else if (key > root->key)
        del(key, root->rightChild);

    else {
        if (root->leftChild == nullptr) {
            Node* temp = root->rightChild;
            delete root;
            root = temp;
        } else if (root->rightChild == nullptr) {
            Node* temp = root->leftChild;
            delete root;
            root = temp;
        } else {
            Node* temp = minNode(root->rightChild);
            root->key = temp->key;
            del(temp->key, root->rightChild);
        }
    }
    if (root == NULL)
        return root;

    root->height = std::max(getHeight(root->leftChild), getHeight(root->rightChild)) + 1;
    Balancing(root, key);
    return root;
}