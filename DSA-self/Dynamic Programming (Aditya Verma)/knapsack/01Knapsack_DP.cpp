/*
0 - 1 Knapsack Problem with bottom-up approach
You are given weights and values of N items, put these items in a knapsack of capacity W to get the maximum total value in the knapsack. Note that we have only one quantity of each item.
In other words, given two integer arrays val[0..N-1] and wt[0..N-1] which represent values and weights associated with N items respectively. Also given an integer W which represents knapsack capacity, find out the maximum value subset of val[] such that sum of the weights of this subset is smaller than or equal to W. You cannot break an item, either pick the complete item, or don’t pick it (0-1 property).

Input:
The first line of input contains an integer T denoting the number of test cases. Then T test cases follow. Each test case consists of four lines.
The first line consists of N the number of items.
The second line consists of W, the maximum capacity of the knapsack.
In the next line are N space separated positive integers denoting the values of the N items,
and in the fourth line are N space separated positive integers denoting the weights of the corresponding items.

Output:
For each testcase, in a new line, print the maximum possible value you can get with the given conditions that you can obtain for each test case in a new line.

Constraints:
1 ≤ T ≤ 100
1 ≤ N ≤ 1000
1 ≤ W ≤ 1000
1 ≤ wt[i] ≤ 1000
1 ≤ v[i] ≤ 1000

Example:
Input:
2
3
4
1 2 3
4 5 1
3
3
1 2 3
4 5 6
Output:
3
0
Explanation:
Test Case 1: With W = 4, you can either choose the 0th item or the 2nd item. Thus, the maximum value you can generate is the max of val[0] and val[2], which is equal to 3.
Test Case 2: With W = 3, there is no item you can choose from the given list as all the items have weight greater than W. Thus, the maximum value you can generate is 0.
*/

#include<iostream>
#include<cstring>
using namespace std;
int t[1001][1001];

int main()
{
	//code
	int z;
	cin>>z;
	while(z--){
	    
	    int n;
	    cin>>n;
	    int W;
	    cin>>W;
	    int *val = new int[n];
	    for(int i=0;i<n;i++)
	    cin>>val[i];
	    
	    int *wt = new int[n];
	    for(int i=0;i<n;i++)
	    cin>>wt[i];
	    
	    //initialization
	    for(int i=0;i<n+1;i++)
	    {
	        for(int j=0;j<n+1;j++)
	        {
	            if(i==0 || j==0)
	                t[i][j]=0;
	        }
	    }
	    
	    //converting choice diagram to code
	    for(int i=1;i<n+1;i++)
	    {
	        for(int j=1;j<W+1;j++)
	        {
	            if(wt[i-1]<=j)
	                t[i][j]=max(val[i-1]+t[i-1][j-wt[i-1]] , t[i-1][j]);
	            else
	                t[i][j]=t[i-1][j];
	        }
	    }
	    
	    cout<<t[n][W]<<endl;
	    
	    delete[] val;
	    delete[] wt;
	}
	return 0;
}

// latest code
#include<bits/stdc++.h>
using namespace std;


 // } Driver Code Ends

class Solution
{
    public:
    //Function to return max value that can be put in knapsack of capacity W.
    int knapSack(int W, int wt[], int val[], int n) 
    { 
       // Your code here
       int dp[n+1][W+1];
       memset(dp, 0, sizeof(dp));
       for(int i=1; i<=n; i++){
           for(int j=1; j<=W; j++){
               if(wt[i-1] <= j){
                   dp[i][j] = max(dp[i-1][j], val[i-1] + dp[i-1][j-wt[i-1]]);
               }
               else
                dp[i][j] = dp[i-1][j];
           }
       }
       return dp[n][W];
    }
};

// { Driver Code Starts.

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
}  // } Driver Code Ends