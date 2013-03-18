#include <iostream>
#include "bst.h"

using namespace std;

class node {
    int key;
    node *left;
    node *right;
    bool isred;

    node(int key) : key(key), left(NULL), right(NULL), isred(true) {}

    friend class LLRBTree;
};

class LLRBTree {
    node *root;

    node *_leftRotate(node *t) {
        node *x = t->right;
        t->right = x->left;
        x->left = t;
        return x;
    }

    node *_rightRotate(node *t) {
        node *x = t->left;
        t->left = x->right;
        x->right = t;
        return x;
    }

    node *_flipColors(node *t) {
        t->left->isred = false;
        t->right->isred = false;
        t->isred = true;
        return t;
    }

    bool _isRed(node *n) {
        if (n == NULL) return false;
        return n->isred;
    }

    node *_put(node *n, int key) {
        if (n == NULL) {
            node *x = new node(key);
            return x;
        }

        if (key <= n->key) {
            n->left = _put(n->left, key);
        } else {
            n->right = _put(n->right, key);
        }

        if (!_isRed(n->left) && _isRed(n->right)) n = _leftRotate(n);
        if (_isRed(n->left) && _isRed(n->left->left)) n = _rightRotate(n);
        if (_isRed(n->left) && _isRed(n->right)) n = _flipColors(n);

        return n;
    }

    void _keys(node *root, queue<int> &q) {
        stack<node *> s(100);
        node *curr;
        if (root) {
            curr = root;
            s.push(curr);
            while (!s.isEmpty()) {
                if (curr && curr->left) {
                    curr = curr->left;
                    if (curr) {
                        s.push(curr);
                        continue;
                    }
                }

                s.pop(curr);
                q.enqueue(curr->key);
                curr = curr->right;
                if (curr) s.push(curr);
            }

        }
    }


public:
    LLRBTree() {
        root = NULL;
    }

    void keys(queue<int> &q) {
        _keys(root, q);
    }

    void put(int key) {
       root =  _put(root, key);
    }
};

int main() {

    LLRBTree T;
    int a[] = {10,440,-1,55,-300,100};
    for (int i=0; i<6; i++) {
        T.put(a[i]);
    }
    queue<int> q(100);
    T.keys(q);
    print_queue(q);
}
