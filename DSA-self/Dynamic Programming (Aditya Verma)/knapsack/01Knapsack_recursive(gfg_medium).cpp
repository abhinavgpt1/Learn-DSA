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

// T(n) = O(2^N)
// S(n) = O(N)
#include<iostream>
using namespace std;
int knapsack(int wt[], int val[], int W, int n){
    
    if(n==0|| W==0){
        return 0;
    }
    
    if(wt[n-1]<=W)
        return max(val[n-1] + knapsack(wt,val,W-wt[n-1],n-1) , knapsack(wt,val,W,n-1));
    else if(wt[n-1]>W)
        return knapsack(wt,val,W,n-1);    
}
int main()
{
	//code
	int z;
	cin>>z;
	while(z--){
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