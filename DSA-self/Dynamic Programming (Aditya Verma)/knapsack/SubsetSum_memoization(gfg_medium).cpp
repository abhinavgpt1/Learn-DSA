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

// Picking elements right to left
class Solution{   
    bool isSubsetHelper(vector<int> &arr, vector<vector<int>> &dp, int sum, int n){
        if(sum == 0) // set = {} is always there
            return true;
        if(n == 0)
            return false;
            
        if(dp[n-1][sum] != -1)
            return dp[n-1][sum];
        
        if(arr[n-1] <= sum)
            return dp[n-1][sum] =
                   isSubsetHelper(arr, dp, sum - arr[n-1], n - 1) ||
                   isSubsetHelper(arr, dp, sum, n - 1);
        else
            return dp[n-1][sum] = isSubsetHelper(arr, dp, sum, n - 1);
    }
public:
    bool isSubsetSum(vector<int>arr, int sum){
        int n = arr.size();
        vector<vector<int>> dp(n, vector<int>(sum + 1, -1));
        return isSubsetHelper(arr, dp, sum, n);
    }
};

/*
- picking elements in left to right fashion
- (old)code w.r.t. old constraints
*/
#include <bits/stdc++.h>
using namespace std;
int dp[1000][1000];
bool checkSubsetSum(int arr[], int n, int sum, int index){
    if(index == n){
        return sum == 0;
    }
    if(dp[index][sum] != -1)
        return dp[index][sum];

    return dp[index][sum] = (checkSubsetSum(arr, n, sum, index + 1) || checkSubsetSum(arr, n, sum - arr[index], index + 1));
}
int main(){
    int arr[] = {2,3,7,8,10};
    int sum = 11;
    memset(dp, -1, sizeof(dp));
    if(checkSubsetSum(arr, sizeof(arr)/sizeof(int), sum, 0))
    cout<<"Present"<<endl;
    else
    cout<<"Not Present"<<endl;
}