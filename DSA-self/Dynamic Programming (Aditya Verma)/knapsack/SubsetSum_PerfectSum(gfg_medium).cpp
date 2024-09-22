/**
 * Perfect Sum Problem
 * -------------------
 * Given an array arr of non-negative integers and an integer sum, 
 * the task is to count all subsets of the given array with a sum equal to a given sum.
 * Note: Answer can be very large, so, output answer modulo 10^9+7.
 * 
 * Expected Time Complexity: O(n*sum)
 * Expected Auxiliary Space: O(n*sum)
 * 
 * Constraints:
 * 1 ≤ n*sum ≤ 10^6
 * 0 ≤ arr[i] ≤ 10^6
 * 
 */

// link: https://www.geeksforgeeks.org/problems/perfect-sum-problem5633/1
// article: https://www.geeksforgeeks.org/count-of-subsets-with-sum-equal-to-x/

/* 
    Note: conventional way of bottom-up fails as #(zero) affect the subset count by 2^#(zero) 
    Note: optimizations like for(int j=sum; j>=arr[i]; j--) where one limit is arr[i] shouldn't be used when dp is 2D
*/

// Solution 1: Bottom-up: O(n*sum), O(sum)
class Solution {
    public:
    int perfectSum(int arr[], int n, int sum)
	{
	    int MOD = 1e9+7;
        vector<int> dp(sum + 1, 0); // dp[i] = subset count when sum=i
        dp[0] = 1; //subject to change if arr[i] = 0
        
        for(int i=0; i<n; i++){
            for(int j=sum; j>=arr[i]; j--){ // this covers arr[i]=0. arr[i]->s1 will be unbounded knapsack scenario
                dp[j] = (dp[j] + dp[j - arr[i]]) % MOD;
            }
        }
        return dp[sum];
	}
};

// Solution 2: Bottom-up: O(n*sum), O(n*sum)
class Solution {
    const int MOD = 1e9 + 7;
	public:
	// NO SORTING - just start from ls=0 to sum
    // conventional way, but starting from ls=0 to sum. This deals 0's and solves {0,0,0} case too
	int perfectSum(int arr[], int n, int sum)
	{
	    vector<vector<int>> dp(n + 1, vector<int>(sum + 1, 0));
	    dp[0][0] = 1; //1 subset exist for sum=0

        for(int pos=1; pos<=n; pos++){
            for(int ls = 0; ls <= sum; ls++){ //iterate from 0 to sum -> so as to not be dependent on first positive element existence
                if(arr[pos - 1] <= ls){
                    dp[pos][ls] = (dp[pos - 1][ls - arr[pos - 1]] + dp[pos - 1][ls])%MOD;
                } else {
                    dp[pos][ls] = dp[pos - 1][ls];
                }
            }
        }
        
        return dp[n][sum];
	}
}

// WRONG: Solution 3: Bottom-up: O(n*sum) + O(nlogn), O(n*sum)
class Solution{
    const int MOD = 1e9 + 7;
	public:
	// Solving by sorting in desc. order and starting from ls=1 to sum -> doesn't solve {0,0,0}, sum=0 case
	int perfectSum(int arr[], int n, int sum)
	{
	    sort(arr, arr+n, greater<int>()); 
	    vector<vector<int>> dp(n + 1, vector<int>(sum + 1, 0));
        for(int i=0; i<n+1; i++){
	        dp[i][0] = 1; //1 subset exist for sum=0
        }

        for(int pos=1; pos<=n; pos++){
            for(int ls = 1; ls <= sum; ls++){
                if(arr[pos - 1] <= ls){
                    dp[pos][ls] = (dp[pos - 1][ls - arr[pos - 1]] + dp[pos - 1][ls])%MOD;
                } else {
                    dp[pos][ls] = dp[pos - 1][ls];
                }
            }
        }
        
        return dp[n][sum]; //always 1 hence WRONG => so start inner loop from j=0 to fix it. no sorting is reqd.
	}
	  
};

// Solution 4: Counting subsets with zero at last by sorting in ascending order
// fails at {0,0,0,0} i.e. there should be atleast 1 non-zero element
class Solution{
    const int MOD = 1e9 + 7;
    int custPow(int base, int n, const int MOD){
        int dp[n+1];
        dp[0] = 1;
        for(int i=1; i<=n; i++){
            dp[i] = ((long long)dp[i-1] * base)%MOD;
        }
        return dp[n];
    }
	public:
	int perfectSum(int arr[], int n, int sum)
	{
	    //sum >= 0
	    //problem doesn't say to count unique subsets
        //total subsets = 2^n
	    
	    //subset calculation is independent of sorting array if elements>0
	    sort(arr, arr+n); 
	    //this will put 0's at top. They won't be counted now in subsets. ans = subsets(num of zeros) * count of subsets with all positive nums
	    
	    // subset != subarray != permutation over zeroes sequence
	    int numZero = count(arr, arr+n, 0);
	    int numSubsetsZero = custPow(2, numZero, MOD);//nc1 + nc2 + nc3 + .. + ncn = 2^n
	    
        vector<vector<int>> dp(n + 1, vector<int>(sum + 1, 0));
        for(int i=0; i<=n; i++)
            dp[i][0] = 1; // 1 subset exist for sum=0
        
        for(int pos=1; pos<=n; pos++){
            for(int ls = 1; ls <= sum; ls++){
                if(arr[pos - 1] <= ls){
                    dp[pos][ls] = (dp[pos - 1][ls - arr[pos - 1]] + dp[pos - 1][ls])%MOD;
                } else {
                    dp[pos][ls] = dp[pos - 1][ls];
                }
            }
        }
        
        return ((long long)dp[n][sum] * numSubsetsZero)%MOD;
	}
};