/**
 * Minimum sum partition
 * ---------------------
 * Given an array arr of size n containing non-negative integers, 
 * the task is to divide it into two sets S1 and S2 
 * such that the absolute difference between their sums is minimum and find the minimum difference
 * 
 * Expected Time Complexity: O(N*|sum of array elements|)
 * Expected Auxiliary Space: O(N*|sum of array elements|)
 * 
 * 
 * Constraints:
 * 1 ≤ N*|sum of array elements| ≤ 10^6
 * 0 < arr[i] <= 10^5
 */

// link: https://www.geeksforgeeks.org/problems/minimum-sum-partition3317/1
// article: https://www.geeksforgeeks.org/partition-a-set-into-two-subsets-such-that-the-difference-of-subset-sums-is-minimum/

// Solution 1: Bottom-up: O(N*sum/2), O(sum/2)
class Solution{
    public:
	int minDifference(int arr[], int n)  { 
	    int sum = accumulate(arr, arr + n, 0);
	    int sumcpy = sum;
        sum /= 2;
        vector<bool> dp(sum + 1, false);
        dp[0] = true;
        //calculation of subset sum can be done in O(sum) space
        for(int pos=1; pos<=n; pos++){
            for(int ls=sum; ls>=1; ls--){ // IMP: ls is from sum to 1. Other way round will be wrong. Optimization: ls>=arr[pos-1]
                if(arr[pos - 1] <= ls)
                    dp[ls] = dp[ls - arr[pos-1]] || dp[ls];
            }
        }
        
	    for(int j=sum; j>=0; j--){
	        if(dp[j])
	            return sumcpy - 2*j;
	    }

	    return INT_MAX; //unreachable
	} 
};

// Solution 2: // Solution 1: Bottom-up: O(N*sum/2), O(N*sum/2)
class Solution{

  public:
	int minDifference(int arr[], int n)  { 
	    // 0 don't make a difference in "existence" of subset sum -> affects in count of subset sum only
	    int sum = accumulate(arr, arr+n, 0);
	    
	    // unnecessary to run for sum
	    // Also, this works for both odd-sum and even-sum
	    int halfsum = sum/2;
	    vector<vector<bool>> dp(n+1, vector<bool>(halfsum+1, 0)); // dp[i][j] - tracks if subset sum is possible when array is [0..i] for sum = j
	    
	    // base case
	    for(int i=0; i<=n; i++) // careful not to run till n-1 i.e. '< n'
	        dp[i][0] = true;
	        
	    // bottom-up
	    for(int pos = 1; pos<=n; pos++){
	        for(int ls = 1; ls<=halfsum; ls++){
	            int value = arr[pos - 1];
	            if(value <= ls)
	                dp[pos][ls] = dp[pos-1][ls-value] || dp[pos-1][ls];
                else
	                dp[pos][ls] = dp[pos-1][ls];
	        }
	    }
	    for(int j=halfsum; j>=0; j--){
	        // considering array = [0...n-1] and checking if sum is possible
	        if(dp[n][j])
	            return sum - 2*j;
	    }
	    return INT_MAX; //unreachable
	} 
};

// Old code with old constraints - works fine for non-negatives too.
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