#include <iostream>

using namespace std;

void print(int a[], int l) {
    cout<<"Array"<<endl;
    for (int i=0; i<l; i++) {
        cout<<a[i]<<" ";
    }
    cout<<endl;
}


void _merge(int a[], int lo, int mid, int hi) {

    int i=lo, j=mid+1;
    int len = sizeof(int) * (hi-lo+1);
    int *tmp = (int *) malloc(len);
    int x = 0;

    while (i <= mid && j <= hi) {
        if (a[i] <= a[j]) {
            tmp[x++] = a[i++];
        } else {
            tmp[x++] = a[j++];
        }
    }

    while (i <= mid) {
        tmp[x++] = a[i++];
    }

    while (j <= hi) {
        tmp[x++] = a[j++];
    }

    memcpy(a+lo, tmp, len);
    free(tmp);
}

void _sort(int a[], int i, int j) {
    if (i>=j)
        return;

    int mid = (j+i)/2;
    _sort(a, i, mid);
    _sort(a, mid+1, j);
    _merge(a, i, mid, j);
}

void sort(int a[], int len) {
    _sort(a, 0, len-1);
}


int main() {

    int t[] = {10, 333, 1, -4, -90, 200,170, 160, 140, 100, 99,98,97,96,95,93,90};
    sort(t, 17);

    print(t, 17);
}



