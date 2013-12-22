#include <iostream>

using namespace std;


void reorder(char *arr, int s, int e) {
    int n = e-s+1;

    if (n<4) {
        return;
    }

    int i;
    if (n % 4 == 0) {
        for (i=s+n/4; i < s+n/2; i++) {
            swap(arr[i], arr[i+n/4]);
        }

        reorder(arr, s, s+n/2-1);
        reorder(arr,s+n/2, e);
    } else if (n % 2 == 0) {
        int mid = (e+s)/2;
        char t = arr[mid];
        for (i=mid; i < e-1; i++) {
            arr[i] = arr[i+1];
        }
        arr[i] = t;

        reorder(arr, s, e-2);
    }
}


int main() {
    char test[] = "abcde12345";
    reorder(test, 0, 9);
    cout<<test<<endl;


}
