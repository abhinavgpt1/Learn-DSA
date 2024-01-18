// right to left
// arr : [], sum = 0 - true
// arr : [2,3,4], sum = 0 - true

// WRONG: https://www.geeksforgeeks.org/subset-sum-problem-osum-space/ which promises S(n) = O(sum)*1 
// We need to store w.r.t. element, eg. [1,2,5]

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
