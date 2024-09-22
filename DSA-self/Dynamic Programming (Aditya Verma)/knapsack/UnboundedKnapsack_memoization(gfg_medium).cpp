/**
 * Knapsack with Duplicate Items
 * -----------------------------
 * Given a set of N items, each with a weight and a value, represented by the array wt and val respectively. 
 * Also, a knapsack with weight limit W.
 * The task is to fill the knapsack in such a way that we can get the maximum profit. 
 * Return the maximum profit.
 * Note: Each item can be taken any number of times.
 * 
 * Expected Time Complexity: O(N*W)
 * Expected Auxiliary Space: O(W)
 * 
 * Constraints:
 * 1 ≤ N, W ≤ 1000
 * 1 ≤ val[i], wt[i] ≤ 100
 */

// link: https://www.geeksforgeeks.org/problems/knapsack-with-duplicate-items4201/1
// article: https://www.geeksforgeeks.org/unbounded-knapsack-repetition-items-allowed/

// (old)code w.r.t. old constraints
#include<iostream>
#include<cstring>
using namespace std;
int t[1000][1000];
int unboundedKnapsack(int wt[], int val[], int W, int n){
    if(n == 0 || W == 0)
    return 0;
    
    if(t[n][W] != -1)
    return t[n][W];
    
    if(wt[n-1] <= W){
        return t[n][W] = max(val[n-1] + unboundedKnapsack(wt, val, W - wt[n-1], n), unboundedKnapsack(wt, val, W, n-1));
    }
    else
        return t[n][W] = unboundedKnapsack(wt, val, W, n-1);
}
int main()
{
	int wt[] = {1,3,4,5};
	int val[] = {1, 4, 5, 7};
    memset(t, -1, sizeof(t));
    int W = 8;
    cout<<unboundedKnapsack(wt, val, W, sizeof(wt)/sizeof(int))<<endl;
	return 0;
}