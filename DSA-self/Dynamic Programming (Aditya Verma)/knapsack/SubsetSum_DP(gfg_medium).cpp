/**
 * Subset Sum Problem
 * ------------------
 * Given an array of non-negative integers, and a value sum, 
 * determine if there is a subset of the given set with sum equal to given sum. 
 * 
 * Expected Time Complexity: O(sum*n)
 * Expected Auxiliary Space: O(sum*n)
 * 
 * Constraints:
 * 1 <= n <= 100
 * 1<= arr[i] <= 100
 * 1<= sum <= 10^4
 */

// link: https://www.geeksforgeeks.org/problems/subset-sum-problem-1611555638/1
// article: https://www.geeksforgeeks.org/subset-sum-problem-dp-25/

// Check application @SubsetSum_EqualSumPartition(leetcode_medium).cpp

// Solution 1: Bottom-up: O(N*sum), O(sum)
class Solution{
    public:
    bool isSubsetSum(vector<int>arr, int sum){
        int accsum = accumulate(arr.begin(), arr.end(), 0);
        if(sum > accsum || sum < 0)
            return false;
        
        int n = arr.size();
        vector<bool> dp(accsum + 1, false);
        dp[0] = true;
        for(int pos=1; pos<=n; pos++){
            // IMP: it is from sum to 1. In case of confusion, just use 2 arrays (curr, prev) and code conventionally. 
            // It isn't unbounded knapsack, and going from left to right will consider same element twice, hence this is a unique technique where we go from right to left just to avoid double element counting.
            for(int ls=accsum; ls>=1; ls--){ // ls>=arr[pos-1] is an optimzation => no need for "if" check
                if(arr[pos - 1] <= ls)
                    dp[ls] = dp[ls - arr[pos-1]] || dp[ls];
            }
        }
        
        return dp[sum];
    }
};

// Old code w.r.t. old constraints: Bottom-up: O(N*sum), O(N*sum) space and time complexity
// Picking elements in right to left fashion
// arr : [], sum = 0 - true
// arr : [2,3,4], sum = 0 - true
#include <bits/stdc++.h>
using namespace std;
bool checkSubsetSum(int arr[], int n, int sum){
    bool dp[1000][1000];
    memset(dp, 0, sizeof(dp));
    // For sum=0, {} is a possible soln. given any arr
    for(int i=1; i<=n; i++){
        dp[i][0] = 1;
    }
    // additional  check is required for negative numbers
    for(int i=1; i<=n; i++){
        for(int j=1; j<=sum; j++){
            if(arr[i-1] <= j)
            dp[i][j] = dp[i-1][j] || dp[i-1][j-arr[i-1]];
            else
            dp[i][j] = dp[i-1][j];
        }
    }
    return dp[n][sum];
}
int main(){
    int arr[] = {2,3,7,8,10};
    int sum = 11;
    if(checkSubsetSum(arr, sizeof(arr)/sizeof(int), sum))
    cout<<"Present"<<endl;
    else
    cout<<"Not Present"<<endl;
}
// similar problem - check if array can be split in 2 subsets of equal sum
// |
// |soln.
// ---> check subset sum for sum(arr)/2

// similar problem - count subsets which sum to given sum
// |
// |soln.
// ---> replace 1. bool dp -> int dp, 2. || -> +
    // similar problem - count subsets with given diff ie. S1 - S2 = diff (s.t. S1 + S2 = Sum)
    // |
    // |soln.
    // ---> check for sum = Sum - 2*S2 = Diff -> calculate S2 => run countSubsetSum on this S2
        // similar problem - target sum -> assign -, + to elements of array s.t. on summing up the elements we get a particular (given) sum (X) - count occurence of this
        // |
        // |soln.
        // ---> it wants us to divide the array into 2 parts s.t. positive subset sum + negative subset sum = X
        // ===> S1 - S2 = X -> above problem
