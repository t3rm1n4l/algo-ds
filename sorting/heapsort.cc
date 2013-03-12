#include <iostream>

using namespace std;

void print(int a[], int l) {
    cout<<"Array"<<endl;
    for (int i=0; i<l; i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}

void _swap(int &a, int &b) {
    a = a^b;
    b = a^b;
    a = a^b;
}

void _shift_up(int a[], int lo, int hi) {
    while (hi > lo && a[hi] > a[hi/2]) {
        swap(a[hi], a[hi/2]);
        hi /= 2;
    }
}

void _shift_down(int a[], int lo, int hi) {
    while (lo*2 <= hi) {
        int c = lo*2;
        if (c < hi && a[c] < a[c+1])
            c++;
        if (a[lo] > a[c]) break;
        swap(a[lo], a[c]);
        lo = c;
    }
}

void _sort(int a[], int lo, int hi) {
    for (int i=hi/2; i>=lo; i--) {
        _shift_down(a, i, hi);
    }

    while (hi>lo) {
        swap(a[lo], a[hi]);
        hi--;
        _shift_down(a,lo, hi);
    }
}

void sort(int a[], int N) {
    _sort(a-1, 1, N);
}

int main() {

    int t[] = {10, 333, 1, -4, -90, 200,170, 160, 140, 100, 99,98,97,96,95,93,90};
    sort(t, 17);

    print(t, 17);
}
