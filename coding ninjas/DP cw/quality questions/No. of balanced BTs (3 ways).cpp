/*
Code : No. of balanced BTs
Send Feedback
Given an integer h, find the possible number of balanced binary trees of height h. You just need to return the count of possible binary trees which are balanced.
This number can be huge, so return output modulus 10^9 + 7.
Write a simple recursive solution.
Input Format :
Integer h
Output Format :
Count % 10^9 + 7
Input Constraints :
1 <= h <= 40
Sample Input 1:
3
Sample Output 1:
15
Sample Input 2:
4
Sample Output 2:
315
*/
//DP
#include<cmath>
int balancedBTs(int h){
    int *dp = new int[h+1];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 3;
    int mod = pow(10, 9) + 7;
    for(int i = 3; i <= h; i++)
    {
        long long int h1 = dp[i - 1];
        long long int h2 = dp[i - 2];
        dp[i] = (h1*h1 % mod + h1*h2 % mod + h1*h2 % mod) % mod;
    }
    return dp[h];
}
/*
//memoization
#include<cmath>
long long int helper(int h, int * dp) {
    
    if(dp[h] != -1)
        return dp[h];
    
    int mod = pow(10, 9) + 7;
    
    long long int h1 = helper(h - 1, dp);
    long long int h2 = helper(h - 2, dp);
    
    return dp[h] = (h1*h1 % mod + h1*h2 % mod + h1*h2 % mod) % mod;
}
int balancedBTs(int h){
    int *dp = new int[h+1];
    dp[0] = 0;
    dp[1] = 1;
    dp[2] = 3;
    for(int i = 3; i <= h; i++)
        dp[i] = -1;
    return (int)helper(h, dp);
}*/

/*


//recursive: wont work for big no.s
int balancedBTs(int h) {
    if(h <= 1) {
        return 1;
    }

    int mod = (int) (pow(10, 9)) + 7;
    int x = balancedBTs(h - 1);
    int y = balancedBTs(h - 2);

    int temp1 = (int)(((long)(x)*x) % mod);
    int temp2 = (int)((2* (long)(x) * y) % mod);
    int ans = (temp1 + temp2) % mod;


    //int ans = (x*x + 2*x*y) % mod;
    return ans;
}