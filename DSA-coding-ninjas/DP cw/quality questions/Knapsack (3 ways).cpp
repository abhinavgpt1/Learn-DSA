/*
Code: Knapsack (Memoization and DP)
Send Feedback
A thief is robbing a store and can carry a maximal weight of W into his knapsack. There are N items and ith item weighs wi and is of value vi. Considering the constraints of maximum weight that knapsack can carry, you have to find and return the maximum value that thief can generate by stealing items.
Note
Space complexity should be O(W).
Input Format :
The first line contains an integers, that denote the value of N. The following line contains N space separated integers, that denote the values of weight of items. The following line contains N space separated integers, that denote the values associated with the items. The following line contains an integer that denote the value of W. W denotes maximum weight that thief can carry.
Output Format :
The first and only line of output contains the maximum value that thief can generate, as described in the task. 
Constraints
1 <= N <= 10^4
1<= wi <= 100
1 <= vi <= 100
Time Limit: 1 second
Sample Input 1 :
4
1 2 4 5
5 4 8 6
5
Sample Output 1 :
13
*/

#include<vector>
// DP
int knapsack(int* weight, int* value, int n, int maxWeight) {
	vector<vector<int>> dp(n + 1, vector<int>(maxWeight + 1, 0));
    for(int i = 1; i<=n ; i++){
        for(int j = 1; j<=maxWeight; j++){
            if(weight[i - 1] <= j)
                dp[i][j] = max(dp[i-1][j], value[i-1] + dp[i-1][j-weight[i-1]]);
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    return dp[n][maxWeight];
}

// memoization
int helper(int* weight, int* value, int n, int maxWeight, vector<vector<int>> &dp) {
    if(n == 0 || maxWeight == 0)
        return 0;
    
    if(dp[n-1][maxWeight] != -1)
        return dp[n-1][maxWeight];
    
    if(weight[n-1] <= maxWeight)
    	return dp[n-1][maxWeight] = max(helper(weight, value, n-1, maxWeight, dp), value[n-1] + helper(weight, value, n-1, maxWeight - weight[n-1], dp));
    else
        return dp[n-1][maxWeight] = helper(weight, value, n-1, maxWeight, dp);
}
int knapsack(int* weight, int* value, int n, int maxWeight) {
	vector<vector<int>> dp(n, vector<int>(maxWeight + 1, -1));
	return helper(weight, value, n, maxWeight, dp);
}

// recursive
#include<vector>
int knapsack(int* weight, int* value, int n, int maxWeight) {
    if(n == 0 || maxWeight == 0)
        return 0;
    
    if(weight[n-1] <= maxWeight)
    	return max(knapsack(weight, value, n-1, maxWeight), value[n-1] + knapsack(weight, value, n-1, maxWeight - weight[n-1]));
    else
        return knapsack(weight, value, n-1, maxWeight);
}