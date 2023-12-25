#include <bits/stdc++.h>
using namespace std;
int dp[1000][1000];
int minCoinCount(int coin[], int n, int sum)
{
    if (sum == 0)
        return 0;
    if (n == 0)
        return INT_MAX;

    if (dp[n][sum] != -1)
        return dp[n][sum];

    if (coin[n - 1] <= sum)
    {
        int ex = minCoinCount(coin, n - 1, sum);
        int inc = minCoinCount(coin, n, sum - coin[n - 1]);
        int x = min(ex, inc);
        if (x == INT_MAX || x == ex)
            return dp[n][sum] = x;
        return dp[n][sum] = x + 1;
    }
    else
        return dp[n][sum] = minCoinCount(coin, n - 1, sum);
}
int minCoinCount_DP(int coin[], int n, int sum)
{
    memset(dp, 0, sizeof(dp));
    for (int i = 1; i <= sum; i++)
        dp[0][i] = INT_MAX;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            if (coin[i - 1] <= j)
            {
                int x = min(dp[i][j - coin[i - 1]], dp[i - 1][j]);
                // if on minimum the coin value is to be excluded -> no +1 in answer
                dp[i][j] = (x == INT_MAX || x == dp[i-1][j] ? x : x + 1);
            }
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    return dp[n][sum];
}
int main()
{
    int coin[] = {2,5,10,1};
    int sum = 27;
    // int coin[] = {1, 2, 3};
    // int sum = 5;
    memset(dp, -1, sizeof(dp));
    cout << minCoinCount(coin, sizeof(coin)/sizeof(int), sum) << endl;
    // cout << minCoinCount_DP(coin, sizeof(coin) / sizeof(int), sum) << endl;
    return 0;
}