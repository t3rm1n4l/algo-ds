#include <iostream>

using namespace std;


void permutations(char *str, int pos, int end) {
    if (pos == end) {
        cout<<str<<endl;
        return;
    }

    char mem[256];
    bzero(mem, 256);
    int i;
    for (i=pos; i <=end; i++) {
        if (!mem[str[i]]) {
            swap(str[i], str[pos]);
            permutations(str, pos+1, end);
            swap(str[i], str[pos]);
            mem[str[i]] = 1;
        }
    }
}


int main() {

    char x[]="1100000";


    permutations(x, 0, 6);
}
