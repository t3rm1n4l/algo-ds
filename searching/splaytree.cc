#include <iostream>
#include "bst.h"

using namespace std;

class node {
    int key;
    node *left;
    node *right;

public:
    node(int k): key(k), left(NULL), right(NULL) {}
    friend class SplayTree;
};

class SplayTree {
    node *root;

    node *_splayIt(node *t, int key) {
        if (t == NULL) {
            return NULL;
        }

        node *N = new node(0);
        node *l, *r, *y;
        l = r = N;

        while (1) {
            if (key < t->key) {
                if (t->left == NULL) {
                    break;
                }
                if (key < t->left->key) {   // Zig - Zig (first Zig)
                    y = t->left;
                    t->left = y->right;
                    y->right = t;
                    t = y;
                }

                if (t->left == NULL) {
                    break;
                }

                r->left = t;  // Zig
                r = t;
                t = t->left;
            } else if (key > t->key) {
                if (t->right == NULL) {
                    break;
                }
                if (key > t->right->key) {
                    y = t->right;
                    t->right = y->left;
                    y->left = t;
                    t = y;
                }

                if (t->right == NULL) {
                    break;
                }

                l->right = t;
                l = t;
                t = t->right;
            } else {
                break;
            }
        }
        l->right = t->left; // Assemble
        r->left = t->right;
        t->left = N->right;
        t->right = N->left;

        delete N;

        return t;
    }

    node *_put(node *t, int key) {
        node *n = new node(key);
        if (t == NULL) {
            return n;
        }

        t = _splayIt(t, key);
        if (key <= t->key) {
            n->right = t;
            n->left = t->left;
            t->left = NULL;
            t = n;
        } else {
            n->left = t;
            n->right = t->right;
            t->right = NULL;
            t = n;
        }

        return t;
    }

    node *_del(node *t, int key, bool &status) {
        node *n;
        status = true;
        if (t == NULL) {
            return NULL;
        }

        t = _splayIt(t, key);
        if (t->key == key) {
            if (t->left == NULL) {
                n = t->right;
            } else {
                n = _splayIt(t->left, key);
                n->right = t->right;
            }
            delete t;
            t = n;
            status = true;
        }

        return t;
    }

    node * _get(node *t, int key, bool &status) {
        status = false;
        if (t == NULL) {
            return NULL;
        }

        t = _splayIt(t, key);
        if (t->key == key) {
            status = true;
        }

        return t;
    }

    void _keys_levelorder(node *t, queue<int> &q) {
        int delim = INT_MAX;
        node *itm = NULL;

        queue<node *> tmpq(100);
        tmpq.enqueue(itm);
        tmpq.enqueue(t);

        while (!tmpq.isEmpty()) {
            tmpq.dequeue(itm);
            if (itm == NULL) {
                if (tmpq.isEmpty()) {
                    return;
                }
                q.enqueue(delim);
                tmpq.enqueue(itm);
            } else {
                q.enqueue(itm->key);
                if (itm->left) {
                    tmpq.enqueue(itm->left);
                }
                if (itm->right) {
                    tmpq.enqueue(itm->right);
                }
            }

        }

    }

    void _keys_inorder(node *t, queue<int> &q) {
        node *curr = t;
        stack<node *> s(100);

        if (curr == NULL) {
            return;
        }
        s.push(curr);

        while (!s.isEmpty()) {
            if (curr && curr->left) {
                s.push(curr->left);
                curr = curr->left;
                if (curr) {
                    continue;
                }
            }

            s.pop(curr);
            q.enqueue(curr->key);
            curr = curr->right;
            if (curr) {
                s.push(curr);
            }
        }
    }

public:
    SplayTree() : root(NULL) {}

    void put(int key) {
        root = _put(root, key);
    }

    bool get(int key) {
        bool st;
        node *n;
        root = _get(root, key, st);
        return st;
    }

    bool del(int key) {
        bool st;
        root = _del(root, key, st);
        return st;
    }

    void keys(queue<int> &q) {
        _keys_levelorder(root, q);
        //_keys_inorder(root,q);
    }

};

int main() {

    SplayTree T;
    int a[] = {10,440,-1,55,-300,100};
    for (int i=0; i<6; i++) {
        T.put(a[i]);
    }
    queue<int> q(100);
    T.keys(q);
    print_queue(q);

    T.get(10);
    T.keys(q);
    print_queue(q);

    T.get(-300);
    T.keys(q);
    print_queue(q);

}
