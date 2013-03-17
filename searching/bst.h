#include <iostream>

using namespace std;

template <typename T>
class queue {
    int N;
    int i,j,size;
    T *store;

public:
    queue(int N) {
        i = j = size = 0;
        store = new T[N];
        this->N = N;
    }

    ~queue() {
        delete [] store;
    }

    bool isEmpty() const {
        return size == 0;
    }

    bool isFull() const {
        return size == N;
    }

    bool enqueue(T &x) {
        if (isFull()) return false;
        size++;
        store[i] = x;
        i = (i+1)%N;
        return true;
    }

    bool dequeue(T &x) {
        if (isEmpty()) return false;
        x = store[j];
        size--;
        j++;
        j = (j+N)%N;
    }

};


template<typename T>
class stack {
    int N;
    int i;
    T *store;

public:
    stack(int N) {
        this->i = 0;
        this->N = N;
        store = new T[N];
    }

    bool isEmpty() {
        return i == 0;
    }

    bool isFull() {
        return i == N;
    }

    bool push(T &x) {
        if (isFull()) return false;
        store[i] = x;
        i++;
        return true;
    }

    bool pop(T &x) {
        if (isEmpty()) return false;
        i--;
        x = store[i];
    }
};

void print_queue(queue<int> &q) {
    int x;
    cout<<"Queue: ";
    while (!q.isEmpty()) {
        q.dequeue(x);
        if (x == INT_MAX) {
            cout<<endl;
            continue;
        }
        cout<<x<<" ";
    }
    cout<<endl;
}
