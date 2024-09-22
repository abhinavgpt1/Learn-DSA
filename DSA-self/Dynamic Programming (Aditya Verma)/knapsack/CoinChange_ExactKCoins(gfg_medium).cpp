/**
 * Another Coin Change Problem
 * ---------------------------
 * Given three integers n, k, target, and an array of coins of size n. 
 * Find if it is possible to make a change of target cents by using an infinite supply of each coin,
 * but the total number of coins used must be exactly equal to k.
 * 
 * Expected Time Complexity: O(n*k*target)
 * Expected Space Complexity: O(k*target)
 * 
 * Constraints:
 * 1 <= n, k, coins[i] <= 100
 * 1 <= target <= 1000
 *
 */

// link: https://www.geeksforgeeks.org/problems/another-coin-change-problem--170647/0
// article: Check editorial in this question

// Solution 1: Bottom-up: O(N*K*Target), O(K*Target)
class Solution {
  public:
    bool makeChanges(int N, int K, int target, vector<int> &coins) {
       // this problem is an extension to 1d array approach of unbounded knapsack where we don't need a dimension to store array element
       // recall: in unbounded knapsack problems you can take one 1d array as dp

        vector<vector<bool>> dp(target + 1, vector<bool>(K+1, false));
        dp[0][0] = true; // when target=0 and coins demanded=0, then the problem is solvable given any N
        
        for(int pos=1; pos<=N; pos++){
            for(int ls=1; ls<=target; ls++){
                if(coins[pos - 1] <= ls){
                    for(int cc=1; cc<=K; cc++){
                        // We want to check, if inclusion/exclusion of coin can achieve sum at a specific coin count
                        // considering coin[i] => @k=k-1, dp[k-1][j-coins[i]] must be true
                        // not considering coin[i] => @k=k, dp[k][j] must be true
                        // doing, dp[k-1][j] isn't right as K coins aren't guaranteed
                        
                        dp[ls][cc] = dp[ls - coins[pos-1]][cc-1] || dp[ls][cc];
                    }
                }
                // else: this coin won't contribute anywhere, so dp[for all k][j] = false
                // in short dp[k][j] = dp[k][j] i.e. why lose (true) if it was set once
            }
            // TLE came due to full execution = N*K*target. 
            // As soon as the sum is achievable, we should returned true
            // loop on n -> loop on target -> loop on K is the most optimal way. Any order change will execute all cases thus leading to TLE
            if(dp[target][K])
                return true;
        }
        return false;
    }
};

// Solution 2: Memoized: : O(N*K*Target), O(K*Target) + stack space
class Solution {
    bool helper(vector<int> &coins, vector<vector<int>> &dp, int K, int target, int N){
        if(K==0)
            return target == 0;
        else if (target<=0 || N <= 0)
            return false;
        
        if(dp[K][target] != -1)
            return dp[K][target];
        
        if(coins[N-1] <= target){
            return dp[K][target] = 
                helper(coins, dp, K-1, target - coins[N-1], N) //consider it again
                || helper(coins, dp, K, target, N-1); //don't considerr it again
        } else {
            return dp[K][target] = helper(coins, dp, K, target, N-1);
        }
    }
  public:
    bool makeChanges(int N, int K, int target, vector<int> &coins) {
        vector<vector<int>> dp(K+1, vector<int>(target + 1, -1));
        return helper(coins, dp, K, target, N);
    }
};

// Solution 3: Memoized:: O(N*K*Target), O(N*K*Target)
class Solution {
  public:
    bool helper(int N, int K, int target, vector<int> &coins, vector<vector<vector<int>>> &dp) {
        if(K == 0)
            return target == 0;
        if(target == 0 || N == 0)
            return false;
        
        if(dp[N][target][K] != -1)
            return dp[N][target][K];
        
        if(coins[N-1] <= target){
            return dp[N][target][K] = helper(N, K - 1, target - coins[N-1], coins, dp) 
            || helper(N-1, K, target, coins, dp);
        } else {
            return dp[N][target][K] = helper(N-1, K, target, coins, dp);
        }
    }
    bool makeChanges(int N, int K, int target, vector<int> &coins) {
        // Now, we want to know a sum is possible by subarray for various coin count
        // This adds a third dimension in dp
        vector<vector<vector<int>>> dp(N+1, vector<vector<int>>(target + 1, vector<int>(K+1, -1)));
        return helper(N, K, target, coins, dp);
    }
};

//Solution 4: recursive
class Solution
{
    // O(2^N), O(N+K) [stack space] soln. with depth till K
public:
    bool makeChanges(int N, int K, int target, vector<int> &coins)
    {
        if (K == 0)
            return target == 0;
        if (target == 0 || N == 0)
            return false;

        if (coins[N - 1] <= target)
        {
            return makeChanges(N, K - 1, target - coins[N - 1], coins) || makeChanges(N - 1, K, target, coins);
        }
        else
        {
            return makeChanges(N - 1, K, target, coins);
        }
    }
};