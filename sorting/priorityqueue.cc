#include <iostream>

using namespace std;

void swap(int &a, int &b) {
    int t = a;
    a = b;
    b = t;
}

void shift_up(int a[], int lo, int hi) {
    while (lo < hi && a[hi] > a[hi/2]) {
        swap(a[hi], a[hi/2]);
        hi /= 2;
    }
}

void shift_down(int a[], int lo, int hi) {
    while (lo*2 <= hi) {
        int c = lo*2;
        if (c < hi && a[c] < a[c+1])
            c++;

        if (a[lo] > a[c]) break;
        swap(a[lo], a[c]);
        lo = c;;
    }
}

typedef struct {
    size_t N;
    int *a;
    int i;
} pq;


void pq_init(pq &x, size_t n) {
    x.a = new int[n];
    x.a++;
    x.N = n;
    x.i = 1;
}

void pq_destroy(pq &x) {
    delete [] (x.a-1);
    x.N = 0;
    x.i = 0;
}

bool pq_put(pq &x, int itm) {
    if (x.i <= x.N) {
        (x.a)[x.i] = itm;
        shift_up(x.a, 1, x.i);
        x.i++;
        return true;
    }
    return false;
}

bool pq_get(pq &x, int &val) {
    if (x.i > 0) {
        val = (x.a)[1];
        x.i--;
        (x.a)[1] = (x.a)[x.i];
        shift_down(x.a, 1, x.i-1);
        return true;
    }
    return false;
}

int main() {
    pq x;
    pq_init(x, 100);

    pq_put(x, 300);
    pq_put(x, 100);
    pq_put(x, 1000);
//    pq_put(x, 500);
    pq_put(x, 10000);



    int a;
    pq_get(x, a);
    cout<<a<<endl;
    pq_get(x, a);
    cout<<a<<endl;
    pq_get(x, a);
    cout<<a<<endl;
    pq_get(x, a);
    cout<<a<<endl;
  //  pq_get(x, a);
  //  cout<<a<<endl;
}



