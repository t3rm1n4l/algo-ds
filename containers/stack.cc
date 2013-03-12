#include <iostream>

using namespace std;

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


int main() {
    stack<int> q(10);
    for (int i=0; i < 20; i++) {
        if (i < 20/2) {
            q.push(i);
        } else {
            int x=6;
            if(q.pop(x))
                cout<<x<<endl;
        }
    }
}
