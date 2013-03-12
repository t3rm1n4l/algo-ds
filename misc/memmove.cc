#include <iostream>

using namespace std;

//1 2 3 4 5 6 7 8 9

int memmove(char *ptr1, char *ptr2, int len) {

    if (ptr1 < ptr2) {

        for (int i=0; i< len; i++) {
            *(ptr1+i) = *(ptr2+i);
        }
    } else {
        for (int i=len; i >= 0; i--) {
            *(ptr1+i) = *(ptr2+i);
        }
    }
}


int main() {

    char x[] = "123 345 678";
    cout<<x<<endl;

    memmove(x+4,x, 6);
    cout<<x<<endl;
}

