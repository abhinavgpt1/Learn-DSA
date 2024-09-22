/**
 * 0 - 1 Knapsack Problem
 * ----------------------
 * You are given weights and values of N items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack.
 * Note that we have only one quantity of each item.
 * In other words, given two integer arrays val[0..N-1] and wt[0..N-1] which represent values and weights associated with N items respectively.
 * Also given an integer W which represents knapsack capacity, find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W.
 * You cannot break an item, either pick the complete item or dont pick it (0-1 property).
 *
 * Expected Time Complexity: O(N*W).
 * Expected Auxiliary Space: O(N*W)
 *
 * Constraints:
 * 1 ≤ N ≤ 1000
 * 1 ≤ W ≤ 1000
 * 1 ≤ wt[i] ≤ 1000
 * 1 ≤ v[i] ≤ 1000
 */
// link: https://www.geeksforgeeks.org/problems/0-1-knapsack-problem0945/1
// article: https://www.geeksforgeeks.org/0-1-knapsack-problem-dp-10/

// Solution 1: O(N*W) time and O(W) space
class Solution
{
public:
	// GFG editorial inspired soln.
	int knapSack(int W, int wt[], int val[], int n)
	{
		int dp[W + 1];
		memset(dp, 0, sizeof(dp));

		for (int i = 1; i < n + 1; i++)
		{
			for (int w = W; w >= 0; w--) // IMP. w is from W to 1 not other way round
			{
				// Finding the maximum value
				if (wt[i - 1] <= w)
					dp[w] = max(dp[w], dp[w - wt[i - 1]] + val[i - 1]);
			}
		}
		// Returning the maximum value of knapsack
		return dp[W];
	}
	/*
	O(N*W) space

			 0 1 2 3 4
		   0 0 0 0 0 0
		   4 0 0 0 0 1
		   5 0 0 0 0 0
		   1 0 3 3 3 3

	O(W) space - calculation happens left to right. Hence looping right to left won't affect result of dp[W]
			 0 3 3 3 3

	O(W) space when loop is from int w=1; w<=W; w++. This is wrong since re-usage of same element happens
			 0 3 6 9 12
	*/
};

// Solution 2: O(N*W) time and O(2W) space
class Solution
{
public:
	int knapSack(int W, vector<int>& wt, vector<int>& val) {
        int n = wt.size();
        vector<vector<int>> dp(2, vector<int>(W+1, 0));
        for(int i=1; i<=n; i++){
            for(int j=1; j<=W; j++){
                if(wt[i-1] <= j)
                    dp[i&1][j] = max(dp[!(i&1)][j - wt[i-1]] + val[i-1], dp[!(i&1)][j]);
                else
                    dp[i&1][j] = dp[!(i&1)][j];
            }
            dp[!(i&1)] = dp[i&1];
        }
        return dp[n&1][W];
    }
};

// Solution 3: O(N*W) space and O(N*W) time
class Solution
{
public:
	// Function to return max value that can be put in knapsack of capacity W.
	int knapSack(int W, int wt[], int val[], int n)
	{
		// Your code here
		int dp[n + 1][W + 1];
		memset(dp, 0, sizeof(dp));
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= W; j++)
			{
				if (wt[i - 1] <= j)
				{
					dp[i][j] = max(dp[i - 1][j], val[i - 1] + dp[i - 1][j - wt[i - 1]]);
				}
				else
					dp[i][j] = dp[i - 1][j];
			}
		}
		return dp[n][W];
	}
};

// Old code w.r.t. old constraints
#include <iostream>
#include <cstring>
using namespace std;
int t[1001][1001];

int main()
{
	// code
	int z;
	cin >> z;
	while (z--)
	{

		int n;
		cin >> n;
		int W;
		cin >> W;
		int *val = new int[n];
		for (int i = 0; i < n; i++)
			cin >> val[i];

		int *wt = new int[n];
		for (int i = 0; i < n; i++)
			cin >> wt[i];

		// base case
		for (int i = 0; i < n + 1; i++)
		{
			for (int j = 0; j < n + 1; j++)
			{
				if (i == 0 || j == 0)
					t[i][j] = 0;
			}
		}

		// converting choice diagram to code
		for (int i = 1; i < n + 1; i++)
		{
			for (int j = 1; j < W + 1; j++)
			{
				if (wt[i - 1] <= j)
					t[i][j] = max(val[i - 1] + t[i - 1][j - wt[i - 1]], t[i - 1][j]);
				else
					t[i][j] = t[i - 1][j];
			}
		}

		cout << t[n][W] << endl;

		delete[] val;
		delete[] wt;
	}
	return 0;
}