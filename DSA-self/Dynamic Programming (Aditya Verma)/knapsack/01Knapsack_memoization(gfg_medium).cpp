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

// T(n) = O(N*W)
// S(n) = O(N*W) + O(N) [O(N) - auxiliary stack space(ASS) has been used for recursion stack]

#include<iostream>
#include<cstring>
using namespace std;
int t[1001][1001];
int knapsack(int wt[], int val[], int W, int n){
    
    if(n==0|| W==0){
        return 0;
    }
    if(t[n][W]!=-1)
        return t[n][W];
        
    if(wt[n-1]<=W)
        return t[n][W]=max(val[n-1] + knapsack(wt,val,W-wt[n-1],n-1) , knapsack(wt,val,W,n-1));
    else if(wt[n-1]>W)
        return t[n][W]=knapsack(wt,val,W,n-1);    
}
int main()
{
	//code
	int z;
	cin>>z;
	while(z--){
	    memset(t,-1,sizeof(t));
	    int n;
	    cin>>n;
	    int w;
	    cin>>w;
	    int *val = new int[n];
	    for(int i=0;i<n;i++)
	    cin>>val[i];
	    
	    int *wt = new int[n];
	    for(int i=0;i<n;i++)
	    cin>>wt[i];
	    
	    cout<<knapsack(wt,val,w,n)<<endl;
	    delete[] val;
	    delete[] wt;
	}
	return 0;
}
// latest
#include<bits/stdc++.h>
using namespace std;
class Solution
{
    public:
    // same as before
    int t[1001][1001];
    //Function to return max value that can be put in knapsack of capacity W.
    int helper(int wt[], int val[], int n, int index, int W) {
        
        if(W <= 0 || index == n)
            return 0;
        
        if(t[index][W] != -1)
            return t[index][W];
            
        if(wt[index] <= W)
            return t[index][W] = max(helper(wt, val, n, index + 1, W), val[index] + helper(wt, val, n, index + 1, W - wt[index]));
        else
            return t[index][W] = helper(wt, val, n, index + 1, W);
        
    }
    int knapSack(int W, int wt[], int val[], int n) 
    { 
       // Your code here
       memset(t, -1, sizeof(t));
       return helper(wt, val, n, 0, W);
    }
};

int main()
 {
    //taking total testcases
    int t;
    cin>>t;
    while(t--)
    {
        //reading number of elements and weight
        int n, w;
        cin>>n>>w;
        
        int val[n];
        int wt[n];
        
        //inserting the values
        for(int i=0;i<n;i++)
            cin>>val[i];
        
        //inserting the weights
        for(int i=0;i<n;i++)
            cin>>wt[i];
        Solution ob;
        //calling method knapSack()
        cout<<ob.knapSack(w, wt, val, n)<<endl;
        
    }
	return 0;
}