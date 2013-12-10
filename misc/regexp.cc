#include <iostream>

using namespace std;

int matchstar(char *str, char *exp, char c);
int matchhere(char *str, char *exp);

int match(char *str, char *exp) {

    if (*exp == '^') {
        return matchhere(str, exp+1);
    }

    do {
        if (matchhere(str, exp)) {
            return 1;
        }
    } while (*str++ != '\0');

    return 0;
}

int matchstar(char *str, char *exp, char c) {

    do {
        if (matchhere(str, exp)) {
            return 1;
        }
    } while (*str != '\0' && (*str++ == c || c == '.'));

    return 0;
}


int matchhere(char *str, char *exp) {

    if (exp[0] == '\0') {
        return 1;
    }

    if (exp[0] == '$' && exp[1] == '\0') {
        return *str == '\0';
    }

    if (exp[1] == '*') {
        return matchstar(str, exp+2, exp[0]);
    }

    if (str[0] != '\0' && (str[0] == exp[0] || exp[0] == '.')) {
        return matchhere(str+1, exp+1);
    }

    return 0;
}


int main() {
    cout<<match("helllo", "^h.l*o")<<endl;
}
