#include <iostream>

using namespace std;

#define R 256

int search(char *src, char *pat) {
    int m = strlen(pat);

    int dfa[R][m];
    int i,X;

    memset(dfa, 0, R*m);

    dfa[pat[0]][0] = 1;

    for (i=1, X=0;i<m; i++) {

        int c;
        for (c=0; c<R; c++) {
            dfa[c][i] = dfa[c][X];
        }

        dfa[pat[i]][i] = i+1;

        X=dfa[pat[i]][X];
    }

    int state = 0;

    for (i=0; i <= strlen(src); i++) {
        state = dfa[src[i]][state];
        if (state == m) {
            return i-(state-1);
        }
    }

    return -1;
}

int main() {

    cout<<search("1234567890123", "0123")<<endl;

}
