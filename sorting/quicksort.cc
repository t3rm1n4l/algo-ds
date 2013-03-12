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

int _partition(int a[], int lo, int hi) {
    int i=lo, j=hi+1;
    int v = a[lo];

    while (true) {
        while (a[++i] < v) {
            if (i == hi) break;
        }

        while (a[--j] > v) {
            if (j == lo) break;
        }

        if (i>=j) break;
        swap(a[i], a[j]);

    }

    swap(a[lo], a[j]);
    return j;
}

void _sort(int arr[], int i, int j) {

    if (i >= j){
        return;
    }

    int p = _partition(arr, i, j);
    _sort(arr, i, p-1);
    _sort(arr, p+1, j);
}


void sort(int arr[], int len) {
    _sort(arr, 0, len-1);
}


int main() {

    int t[] = {10, 333, 1, -4, -90, 200,170, 160, 140, 100, 99,98,97,96,95,93,90};
    sort(t, 17);

    print(t, 17);
}



