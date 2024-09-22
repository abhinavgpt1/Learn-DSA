/**
 * Coin Change (Count Ways)
 * ------------------------
 * Given an integer array coins[] of size N representing different denominations of currency and an integer sum, 
 * find the number of ways you can make sum by using different combinations from coins[].
 * Note: Assume that you have an infinite supply of each type of coin. 
 * And you can use any coin as many times as you want.
 * 
 * Expected Time Complexity: O(sum*N)
 * Expected Auxiliary Space: O(sum)
 * 
 * Constraints:
 * 1 <= sum, N, coins[i] <= 10^3
 * 
 */
// link: https://www.geeksforgeeks.org/problems/coin-change2448/1
// link: https://leetcode.com/problems/coin-change-ii/description/
// article: https://www.geeksforgeeks.org/coin-change-dp-7/

// Solution 1: Bottom-up: O(N*sum), O(sum)
#define lli long long int
class Solution {
  public:
    long long int count(int coins[], int N, int sum) {

        vector<lli> dp(sum + 1, 0);
        dp[0] = 1; // 1 way to make sum = 0

        for(int i=0; i<N; i++){
            for(int j=coins[i]; j<=sum; j++){ // no need to start from j=1. This will save the "if" check
                dp[j] += dp[j - coins[i]];
            }
        }
        // memoization using this way will lead to double counting as we won't be able to skip exclusion case because of its top-down approach
        // You can clearly see that in bottom-up (line 31) we are constantly updating dp[j] which means dp[j] it isn't fixed...since we have return statement to check dp[j] != -1 in top-down you will get wrong ans
        return dp[sum];
    }
};

// Solution 2: Memoization: O(sum*N), O(sum*N)
typedef long long int lli;
class Solution {
    long long int countHelper(int coins[], vector<vector<lli>> &dp, int N, int sum) {
        // base case return value depends on how the entity contributes in the ans
        if(sum == 0) //vs min count of coins when sum=0 is 0 - https://www.geeksforgeeks.org/problems/number-of-coins1824/0
            return 1;
        if(N == 0) // no way exist when coins are empty except when sum=0
            return 0;
            
        if(dp[N][sum] != -1)
            return dp[N][sum];

        if(coins[N - 1] <= sum){
            return dp[N][sum] = 
            countHelper(coins, dp, N, sum - coins[N-1]) + countHelper(coins, dp, N - 1, sum);
        } 
        else 
            return dp[N][sum] = countHelper(coins, dp, N - 1, sum);
    }
  public:
    long long int count(int coins[], int N, int sum) {
        vector<vector<lli>> dp(N + 1, vector<lli>(sum + 1, -1));
        return countHelper(coins, dp, N, sum);
    }
};


// Old code: Memoized
class Solution
{
public:
    long long int t[1001][1001];
    Solution(){
        memset(t, -1, sizeof(t));
    }
    long long int count(int S[], int m, int n){
        if (n == 0)
            return 1;
        if (m == 0)
            return 0;

        if (t[m][n] != -1)
            return t[m][n];

        if (S[m - 1] <= n)
            return t[m][n] = count(S, m - 1, n) + count(S, m, n - S[m - 1]);
        else
            return t[m][n] = count(S, m - 1, n);
    }
};

// DP
class Solution{
  public:
    long long int t[1001][1001];
    long long int count(int S[], int m, int n) {

        memset(t, 0, sizeof(t));
        for(int i=0; i<m; i++)
        t[i][0] = 1;
        
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(S[i-1] <= j)
                t[i][j] = t[i][j-S[i-1]] + t[i-1][j];
                else
                t[i][j] = t[i-1][j];;
            }
        }
        return t[m][n];
    }
};
