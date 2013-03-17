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

    bool isEmpty() {
        return size == 0;
    }

    bool isFull() {
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
        j = (j+1)%N;
    }

};

int main() {
    queue<int> q(10);
    for (int i=0; i < 20; i++) {
        /*
        if (i%2 == 0) {
            q.enqueue(i);
            cout<<i<<endl;
        } else {
            int x;
            q.dequeue(x);
            cout<<x<<endl;
        }
        */


        if (i < 20/2) {
            q.enqueue(i);
        } else {
            int x=6;
            if(q.dequeue(x))
                cout<<x<<endl;
        }

    }
    cout<<"isempty "<<q.isEmpty()<<endl;
}
