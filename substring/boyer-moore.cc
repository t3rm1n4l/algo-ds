#include <iostream>

using namespace std;

#define R 256

int search(char *src, char *pat) {

    int m,n,i,j;
    m = strlen(pat);
    n = strlen(src);
    int hash[R];

    for (i=0; i<R; i++) {
        hash[i] = -1;
    }

    for (i=0; i<m; i++) {
        hash[pat[i]] = i;
    }

    int skip;

    for (i=0; i <= n-m; i+=skip) {
        skip = 0;
        for (j=m-1; j>=0; j--) {
            if (src[i+j] != pat[j]) {
                skip = j - hash[src[i+j]];

                if (skip < 0) {
                    skip = 1;
                }
                break;
            }


        }

        if (skip == 0) {
            return i;
        }

    }

    return -1;
}

int main() {

    cout<<search("1234567890123", "0123")<<endl;

}
