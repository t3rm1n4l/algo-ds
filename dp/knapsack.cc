#include <iostream>

using namespace std;

int max_sackval(int W, int w[], int v[], int count) {
    int sum[W+1][count+1];
    int i,j;

    memset(sum, 0, sizeof(sum));

    for (i=1; i<=W; i++) {
        for(j=1; j<=count; j++) {
            if (w[j-1] <= i) {
                sum[i][j] = max(v[j-1] + sum[i - w[j-1]][j-1], sum[i][j-1]);
            } else {
                sum[i][j] = sum[i][j-1];
            }
        }
    }

    return sum[W][count];

}


int main() {

    int val[] = {60, 100, 120};
        int wt[] = {10, 20, 30};
            int  W = 50;
    cout<<max_sackval(W, wt, val, 3)<<endl;
}
