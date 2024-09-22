/**
 * 322. Coin Change
 * -----------------------
 * You are given an integer array coins representing coins of different denominations and an integer amount representing a total amount of money.
 * Return the fewest number of coins that you need to make up that amount. 
 * If that amount of money cannot be made up by any combination of the coins, return -1.
 * You may assume that you have an infinite number of each kind of coin.
 * 
 * Constraints:
 * 1 <= coins.length <= 12
 * 1 <= coins[i] <= 2^31 - 1
 * 0 <= amount <= 10^4
 */

// link1 - https://leetcode.com/problems/coin-change/description/
// link2 - https://www.geeksforgeeks.org/problems/number-of-coins1824/1
// article - https://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/

// don't confuse min coins with no. of ways to sum

// Solution 1: Bottom-up: O(N*W), O(W)
class Solution {
public:
    int coinChange(vector<int> &coins, int sum) {
        // unbounded knapsack with one 1d dp
        // optimized: https://leetcode.com/problems/coin-change/submissions/1395598896/ 
            // -> since max(amount) = 10^4 => no need for INT_MAX ..keep it 1e4+1 since max ans can be all 1s i.e. 10^4
            // -> inner loop can star from j=coin[i]
        vector<int> dp(sum + 1, INT_MAX);
        dp[0] = 0; // min count to sum to 0

        for(int i=0; i<coins.size(); i++){
            for(int j=1; j<=sum; j++){ // start from j=coins[i] -> no need of if check
                if(coins[i] <= j){
                    int x = dp[j-coins[i]];
                    if(x != INT_MAX)
                        x++;
                    dp[j] = min(dp[j], x); //x => dp[j-coins[i]] + 1
                }
                //else: this coin will contribute nothing. moreover puts dp[i] as INT_MAX which already is due to intialization
            }
        }
        return dp[sum] == INT_MAX ? -1 : dp[sum];
    }
    // same approach can be made for top-down because of its nature of algo -> dp[sum] may not be the optimal soln. stored (you can clearly see that in bottom-up too we are constantly updating dp[j] which means it isn't fixed).
    // in top-down we often return if(dp[] != -1)...since it is not fixed/neccessarily optimal we get a wrong ans
};

// Solution 2: Bottom-up: O(N*W), O(N*W)
class Solution{
    // optimzation: use dp of length 2*W - https://leetcode.com/problems/coin-change/submissions/1393693859/
    // initialization for dp[0][j]=(INT_MAX -1) as done by Aditya Verma will not work if sum<=INT_MAX
	public:
	int minCoins(vector<int> &coins, int n, int sum) {
	    //Base case 1: minimum coins to get zero sum = 0
	    vector<vector<int>> dp(n + 1, vector<int>(sum + 1, 0));
	    for(int j=1; j<=sum; j++){ //careful here, 1 (not 0) to sum, and also alongside sum (not coins)
	        dp[0][j] = INT_MAX; //Base case 2: non-zero sum with zero coins is impossible
	    }
	    
	    // bottom-up
	    for(int pos=1; pos<=n; pos++){
	        for(int ls=1; ls<=sum; ls++){ // no need to start from 0 like subset sum count for non-negative elements
        	    if(coins[pos-1] <= ls){
        	        int inclusion = dp[pos][ls - coins[pos - 1]]; //careful here to use same element again
        	        int exclusion = dp[pos - 1][ls];
        	        if(inclusion != INT_MAX)
        	            inclusion += 1;
        	        dp[pos][ls] = min(inclusion, exclusion);
        	    } else {
        	        dp[pos][ls] = dp[pos - 1][ls];
        	    }
	        }
	    }
	    if(dp[n][sum] == INT_MAX)
	        return -1;
	    return dp[n][sum];
	}
}

// Solution 3: Memoization: O(N*W), O(N*W) + stack space (O(N+W))
class Solution{
	int minCoinsHelper(vector<int> &coins, vector<vector<int>> &dp, int M, int V) {
	    if(V == 0) //zero coins for zero sum
	        return 0;
	    if(M == 0) //non-zero sum with zero coins is impossible
            return INT_MAX;
            
	    if(dp[M][V] != -1)
	        return dp[M][V];

	    if(coins[M-1] <= V){
	        int inclusion = minCoinsHelper(coins, dp, M, V - coins[M-1]);
	        int exclusion = minCoinsHelper(coins, dp, M - 1, V);
	        if(inclusion != INT_MAX)
	            inclusion+=1;
	        return dp[M][V] = min(inclusion, exclusion);
	    } else {
	        return dp[M][V] = minCoinsHelper(coins, dp, M - 1, V);
	    }
	}
	public:
	int minCoins(vector<int> &coins, int M, int V) {
	    // dp[i][0] and dp[0][j] will be unused
	    vector<vector<int>> dp(M + 1, vector<int>(V + 1, -1));
	    int ans = minCoinsHelper(coins, dp, M, V);
	    if(ans == INT_MAX)
	        return -1;
	    return ans;
	}
};

// Old code - main logic @ coin[i - 1] <= sum
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

// Old - Answers why to use INT_MAX-1 (Aditya Verma's soln.)
// (This)>> Won't be asked, but what if sum=INT_MAX? -> then this would fail.period.
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