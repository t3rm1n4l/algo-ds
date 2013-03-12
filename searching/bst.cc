#include <iostream>
#include <assert.h>
#include "bst.h"

using namespace std;

class node {
public:
    node *left;
    node *right;
    int key;
    int size;

    node(int key) {
        this->key = key;
        this->size = 1;
        left = right = NULL;
    }
};

class BST {
public:
    void put(int key) {
       root =  _put(root, new node(key));

    }

    bool get(int key) {
        node *t = _get(root, key);
        if (t) return t->key == key;
        else return false;
    }

    int min() {
        node *t = _min(root);
        if (t) {
            return t->key;
        }
        return INT_MAX;
    }

    bool del(int key) {
        node *t = _get(root, key);
        if (t) {
            root = _del(root, key);
            return true;
        }

        return false;
    }

    int size() {
        return _size(root);
    }

    void keys(queue<int> &q) {
        _keys(root, q);
    }

    BST() {
        root = NULL;
    }

private:
    node *root;

    int _size(node *root) {
        if (root)
            return root->size;
        return 0;
    }

    node *_put(node *root, node *itm) {
        if (root == NULL) {
            return itm;
        } else if (root->key >= itm->key) {
            root->left = _put(root->left, itm);
        } else {
            root->right = _put(root->right, itm);
        }

        root->size = 1 + _size(root->left) + _size(root->right);

        return root;
    }

    node *_get(node *root, int key) {
        if (root == NULL) {
            return NULL;
        } else if (root->key == key) {
            return root;
        } else if (key < root->key) {
            return _get(root->left, key);
        } else {
            return _get(root->right, key);
        }

    }

    node *_min(node *root) {
        if (root == NULL){
            return NULL;
        } else if (root->left) {
            return _min(root->left) ;
        }

        return root;
    }

    node *_delMin(node *root) {
        if (root) {
            if (root->left == NULL) return root->right;
            root->left = _delMin(root->left);
            root->size = 1 + _size(root->left) + _size(root->right);
        }

        return root;
    }

    node *_del(node *root, int key) {
        if (root) {
            if (root->key > key) {
                root->left = _del(root->left, key);
            } else if (root->key < key) {
                root->left = _del(root->right, key);
            } else {
                if (root->left == NULL) return root->right;
                if (root->right == NULL) return root->left;
                node *n = root;
                root = _min(root->right);
                root->left = n->left;
                root->right = _delMin(root->right);
                delete n;
            }

        }

        root->size = _size(root->right) + _size(root->left) + 1;
        return root;
    }


    /*
     * Recursive inorder
    void _keys(node *root, queue<int> &q) {
        if (root) {
            if (root->left) {
                _keys(root->left, q);
            }

            q.enqueue(root->key);

            if (root->right) {
                _keys(root->right, q);
            }
        }
    }
    */

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

};

int main() {

    BST b;
    int a[] = {10,440,-1,55,-300,100};
    for (int i=0; i<6; i++) {
        b.put(a[i]);
    }

    cout<<b.min()<<endl;

    /*
    for (int i=0; i<6; i++) {
       cout<<b.get(a[i])<<endl;
    }
    */
    cout<<b.size()<<endl;
    queue<int> q(100);
    b.keys(q);
    print_queue(q);

}
