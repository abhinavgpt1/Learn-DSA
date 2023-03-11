/*
Loot Houses
Send Feedback
A thief wants to loot houses. He knows the amount of money in each house. He cannot loot two consecutive houses. Find the maximum amount of money he can loot.
Input format :
The first line of input contains an integer value of 'n'. It is the total number of houses.

The second line of input contains 'n' integer values separated by a single space denoting the amount of money each house has.
Output format :
Print the the maximum money that can be looted.
Constraints :
0 <= n <= 10 ^ 4

Time Limit: 1 sec
Sample Input 1 :
6
5 5 10 100 10 5
Sample Output 1 :
110
Sample Input 2 :
6
10 2 30 20 3 50
Sample Output 2 :
90
Explanation of Sample Output 2 :
Looting first, third, and the last houses([10 + 30 + 50]) will result in the maximum loot, and all the other possible combinations would result in less than 90.
*/

// recursive
int helper(int *arr, int n, int index){

    if(index >= n)
        return 0;
    
    int not_taken = helper(arr, n, index + 1);
    int taken = helper(arr, n, index + 2) + arr[index];
    return max(taken, not_taken);
}
int maxMoneyLooted(int *arr, int n)
{
    return helper(arr, n, 0);
}

// memoization
int helper(int *arr, int n, int index, int *dp){

    if(index >= n)
        return 0;
    if(dp[index] != -1)
        return dp[index];
    
    int not_taken = helper(arr, n, index + 1, dp);
    int taken = helper(arr, n, index + 2, dp) + arr[index];
    return dp[index] = max(taken, not_taken);
}
int maxMoneyLooted(int *arr, int n)
{
    int *dp = new int[n];
    for(int i=0; i<n; i++)
        dp[i] = -1;
    return helper(arr, n, 0, dp);
}

// dp - as per recursion and memoization approaches
int maxMoneyLooted(int *arr, int n)
{
    int *dp = new int[n];
    for(int i=0; i<n; i++)
        dp[i] = -1;
    
//     as per recursive & memoization approach
    for(int i=n-1; i>=0; i--){
    	if(i == n - 1)
            dp[i] = arr[i];
        else if(i ==  n-2)
            dp[i] = max(arr[n-1], arr[n-2]);
        else{
            int x = arr[i] + dp[i + 2];//taken ith house
            int y = dp[i + 1];//rejected ith house
            dp[i] = max(x, y);
        }
            
    }
    
    return dp[0];
}

// dp - ninjas way
int maxMoneyLooted(int *arr, int n)
{
    int *dp = new int[n];
    for(int i=0; i<n; i++)
        dp[i] = -1;
    
//     going left to right - bottom up
//     in earlier approaches - recursive and memoization we used top down approach
    for(int i=0; i<n; i++){
    	if(i == 0)
            dp[i] = arr[i];
        else if(i == 1)
            dp[i] = max(arr[0], arr[1]);
        else
            dp[i] = max(arr[i] + dp[i-2], dp[i-1]);
    }
    
    return dp[n-1];
}

// memoization but using set - unnecessary
#include<set>
int helper(int *arr, int n, int index, set<int> housesLooted, int *dp){

    if(index >= n)
        return 0;
    if(dp[index] != -1)
        return dp[index];
    
    
    int not_taken = helper(arr, n, index + 1, housesLooted, dp);
    housesLooted.insert(index);
    int taken = helper(arr, n, index + 2, housesLooted, dp) + arr[index];
    return dp[index] = max(taken, not_taken);
}
int maxMoneyLooted(int *arr, int n)
{
    int *dp = new int[n];
    for(int i=0; i<n; i++)
        dp[i] = -1;
    set<int> housesLooted;
    return helper(arr, n, 0, housesLooted, dp);
}