/**
 * Rod Cutting
 * -----------
 * Given a rod of length N inches and an array of prices, price[]. 
 * price[i] denotes the value of a piece of length i. 
 * Determine the maximum value obtainable by cutting up the rod and selling the pieces.
 * Note: Consider 1-based indexing.
 * 
 * Expected Time Complexity: O(N^2)
 * Expected Auxiliary Space: O(N)
 * 
 * Constraints:
 * 1 ≤ N ≤ 1000
 * 1 ≤ Ai ≤ 10^5
*/

// link: https://www.geeksforgeeks.org/problems/rod-cutting0840/1
// article: https://www.geeksforgeeks.org/cutting-a-rod-dp-13/

// Solution 1: Bottom-up: O(N*(N+1)/2) ~O(N^2), S(n) = O(N)
class Solution{
    public:
    int cutRod(int price[], int n) {
        // unbounded knapsack, so think in 1D
        // sum and length of array, both equals n
        vector<int> dp(n+1, 0);
        for(int piece=1; piece<=n; piece++){
            for(int rodLen=piece; rodLen<=n; rodLen++){ //rodLen= 1->piece will contribute nothing
                dp[rodLen] = max(price[piece - 1] + dp[rodLen - piece], dp[rodLen]);
            }
        }
        // memoization(S(n) = O(n)) this way isn't possible since dp[i] is not fixed, but in top-down we tend to return dp[i] once set
        return dp[n];
    }
};
// Solution 2: Bottom-up(old, explained): O(N^2), S(n) = O(N)
class Solution{
  public:
    int cutRod(int price[], int n) {
        // Expansion of problem:
        // We need to make sum=n, where the commodities are also N (with weight 1 to N) with each having profit value
        // The commodity, i.e. variable length rods range from 1 to N i.e. length[i] = i + 1. Length array can be different too
        // So, we need to pick commodity in unbounded knapsack fashion to get max. profit
        vector<int> dp(n+1, 0);
        // base case is solved already
        for(int pos=1; pos<=n; pos++){
            for(int ls=1; ls<=n; ls++){
                if(pos <= ls) //pos is index & weight here
                    dp[ls] = max(price[pos - 1] + dp[ls - pos], dp[ls]);
            }
        }
        return dp[n];
    }
};

// Solution 3: Memoization: O(N^2), O(N^2)
class Solution{
    int helper(int price[], vector<vector<int>> &dp, int sum, int n) {
        if(sum == 0)
            return 0; // zero profit for 0 length rod
        if(n == 0)
            return 0; // zero profit when no rod is rem.
        
        if(dp[n][sum] != -1)
            return dp[n][sum];
        if(n <= sum){
            return dp[n][sum] = max(
                price[n-1] + helper(price, dp, sum - n, n),
                helper(price, dp, sum, n-1));
        } else {
            return dp[n][sum] = helper(price, dp, sum, n-1);
        }
    }
  public:
    int cutRod(int price[], int n) {
        // Expansion of problem:
        // We need to make sum=n, where the commodities are also N (with weight 1 to N) with each having profit value
        // So, we need to pick commodity in unbounded knapsack fashion to get max. profit
        vector<vector<int>> dp(n+1, vector<int>(n+1, -1));
        return helper(price, dp, n, n);
    }
};

// Old code - solves generic piece array scenario
#include <iostream>
using namespace std;
int t[101][101];
int rodCutting(int length[], int price[], int n)
{
    // n is the size of rod
    // n is the size of length array - i.e. type of cuttings possible - might be different 
        // --> in such case length array -> weight array and price array -> val array with different lengths
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == 0 || j == 0)
                t[i][j] = 0;
        }

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {

            if (length[i - 1] <= j)
            {
                t[i][j] = max(price[i - 1] + t[i][j - length[i - 1]], t[i - 1][j]);
            }
            else if (length[i - 1] > j)
            {
                t[i][j] = t[i - 1][j];
            }
        }
    }

    return t[n][n];
}
int main()
{
    // code
    int z;
    cin >> z;
    int length[100];
    int price[100];

    for (int i = 0; i < 100; i++)
        length[i] = i + 1;

    while (z--)
    {

        int n;
        cin >> n;

        for (int i = 0; i < n; i++)
            cin >> price[i];

        cout << rodCutting(length, price, n) << endl;
    }
    return 0;
}