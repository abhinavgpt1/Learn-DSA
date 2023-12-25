#include <bits/stdc++.h>
using namespace std;
int dp[1000][1000];
int minCoinCount_DP(int coin[], int n, int sum)
{
    memset(dp, 0, sizeof(dp));
    // this method won't work only if coin:[1,1,1,1,..,1] and sum = INT_MAX -> will give ans INT_MAX - 1
    for (int i = 1; i <= sum; i++)
    {
        dp[0][i] = INT_MAX - 1;

        // initialising for coin 1
        if (i % coin[0] == 0)
            dp[1][i] = i / coin[0];
        else
            dp[1][i] = INT_MAX - 1;
    }
    for (int i = 2; i <= n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            // no cell will have INT_MAX in it
            if (coin[i - 1] <= j)
                dp[i][j] = min(dp[i][j - coin[i - 1]] + 1, dp[i - 1][j]);
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n][sum];
}
int main()
{
    int coin[] = {2, 5, 10, 1};
    int sum = 27;
    // int coin[] = {1, 2, 3};
    // int sum = 5;
    memset(dp, -1, sizeof(dp));
    cout << minCoinCount_DP(coin, sizeof(coin) / sizeof(int), sum) << endl;
    return 0;
}