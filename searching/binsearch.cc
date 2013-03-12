#include <iostream>

using namespace std;

int search(int a[], int lo, int hi, int itm) {
    int i=lo, j=hi, mid;

    while (i<=j) {
        mid = i + (j-i+1)/2;
        if (a[mid] == itm) {
            return mid;
        } else if (a[mid] > itm) {
            j = mid-1;
        } else {
            i = mid+1;
        }
    }

    return -1;
}

int rotatedsearch(int a[], int lo, int hi, int itm) {

    int mid = lo + (hi-lo+1)/2;
    if (a[mid] == itm) {
        return mid;
    } else if (a[mid] < a[hi]) {
        if (a[mid] < itm && itm <= a[hi]) {
            return search(a, mid+1, hi, itm);
        } else {
            return rotatedsearch(a, lo, mid-1, itm);
        }
    } else {
        if (a[mid] > itm && itm >= a[lo]) {
            return search(a, lo, mid-1, itm);
        } else {
            return rotatedsearch(a, mid+1, hi, itm);
        }
    }
    return -1;
}

int main() {
    int x[] = {1000, 2000, 100,200,300,800};

    cout<<rotatedsearch(x, 0, 5, 2000);
}
