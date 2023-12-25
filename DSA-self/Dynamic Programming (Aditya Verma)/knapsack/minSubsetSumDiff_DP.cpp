#include <bits/stdc++.h>
using namespace std;
int minSubsetSumDiff(int arr[], int n, int sumArr)
{
    bool dp[1000][1000];
    memset(dp, 0, sizeof(dp));
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = true;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= sumArr; j++)
        {
            if (arr[i - 1] <= j)
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
            else
                dp[i][j] = dp[i - 1][j];
        }
    }
    // 30/2 = 15 => 2j - sum >=0
    // 31/2 = 15 => 2j - sum < 0 for first iteration
    for (int j = sumArr / 2 + (sumArr%2); j <= sumArr; j++)
    {
        if (dp[n][j])
            return 2 * j - sumArr;
    }
    return INT_MIN;
}
int main()
{
    int arr[] = {2, 3, 7, 8, 12};
    int sumArr = 0;
    sumArr = accumulate(arr, arr + sizeof(arr) / sizeof(int), 0);
    cout << minSubsetSumDiff(arr, sizeof(arr) / sizeof(int), sumArr) << endl;
}