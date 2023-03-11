#include <iostream>
#include <cstring>
using namespace std;
int unboundedKnapsack(int wt[], int val[], int W, int n)
{
    static int t[1000][1000];
    memset(t, 0, sizeof(t));
    // function call i.e. call stack - 10^5 space of array - OK
    // global declaration - upto 10^8
    for(int i=1; i<=n; i++){
        for(int j=1; j<=W; j++){
            if(wt[i-1] <= j)
            t[i][j] = max(val[i-1] + t[i][j - wt[i-1]], t[i-1][j]);
            else
            t[i][j] = t[i-1][j];
        }
    }
    return t[n][W];
}
int main()
{
    int wt[] = {1, 3, 4, 5};
    int val[] = {1, 4, 5, 7};
    int W = 8;
    cout << unboundedKnapsack(wt, val, W, sizeof(wt) / sizeof(int)) << endl;
    return 0;
}