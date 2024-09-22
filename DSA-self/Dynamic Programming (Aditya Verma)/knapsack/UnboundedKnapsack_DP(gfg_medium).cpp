/**
 * Knapsack with Duplicate Items
 * -----------------------------
 * Given a set of N items, each with a weight and a value, represented by the array wt and val respectively. 
 * Also, a knapsack with weight limit W.
 * The task is to fill the knapsack in such a way that we can get the maximum profit. 
 * Return the maximum profit.
 * Note: Each item can be taken any number of times.
 * 
 * Expected Time Complexity: O(N*W)
 * Expected Auxiliary Space: O(W)
 * 
 * Constraints:
 * 1 ≤ N, W ≤ 1000
 * 1 ≤ val[i], wt[i] ≤ 100
 */

// link: https://www.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1
// article: https://www.geeksforgeeks.org/unbounded-knapsack-repetition-items-allowed/

/* 1D dp solutions are possible more for unbounded knapsack and likewise problems */

// Solution: Bottom-up: O(n*sum), O(sum)
class Solution{
public:
    int knapSack(int n, int sum, int val[], int wt[])
    {
        vector<int> dp(sum + 1, 0); //dp[i] = profit at sum=i
        
        for(int i=0; i<n; i++){
            for(int j=wt[i]; j<=sum; j++){
                dp[j] = max(dp[j], val[i] + dp[j-wt[i]]);
            }
        }
        // since dp[i] is updating again and again, so memoization can work wirh 1D dp since top-down returns once dp[i]!=-1
        return dp[sum];
    }
};

// Old code w.r.t. old constraints
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