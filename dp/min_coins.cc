#include <iostream>

using namespace std;

int min_coins(int sum, int coins[], int count) {
    int sol[sum+1];
    int c, bal, m;
    sol[0] = 0;

    for (m=1; m <= sum; m++) {
        for (c=0; c<count; c++) {
            bal = m - coins[c];
            if (m >= coins[c] && sol[m] > 1+sol[bal]) {
                sol[m] = 1+sol[bal];
            }
        }
    }

    return sol[sum];
}


int main() {

    int coins[] = {1,2,3,4,5};
    cout<<min_coins(10, coins, 5)<<endl;
}
