/*
Ways To Make Coin Change
Send Feedback
For the given infinite supply of coins of each of denominations, D = {D0, D1, D2, D3, ...... Dn-1}. You need to figure out the total number of ways W, in which you can make the change for Value V using coins of denominations D.
Return 0 if the change isn't possible.
Input Format
The first line of the input contains an integer value N, which denotes the total number of denominations.

The second line of input contains N values, separated by a single space. These values denote the value of denomination.

The third line of the input contains an integer value, that denotes the value of V.
Output Format
Print the total total number of ways i.e. W.
Constraints :
1 <= n <= 10
1 <= V <= 1000

Time Limit: 1sec
Sample Input 1 :
3
1 2 3
4
Sample Output 1 :
4
Explanation to Sample Input 1 :
Number of ways are - 4 total i.e. (1,1,1,1), (1,1, 2), (1, 3) and (2, 2).
Sample Input 2 :
6
1 2 3 4 5 6
250
Sample Output 2 :
13868903
*/

// recursive
int countWaysToMakeChange(int denominations[], int numDenominations, int value){
	if(numDenominations == 0)
        return 0;
    if(value == 0)
        return 1;
    if(denominations[numDenominations - 1] <= value){
        return countWaysToMakeChange(denominations, numDenominations, value - denominations[numDenominations - 1]) + countWaysToMakeChange(denominations, numDenominations - 1, value);
    }
    else
        return countWaysToMakeChange(denominations, numDenominations - 1, value);
}

// memoization
int helper(int denominations[], int numDenominations, int value, int**dp){
	if(numDenominations == 0)
        return 0;
    if(value == 0)
        return 1;
    
    if(dp[numDenominations][value] != -1)
        return dp[numDenominations][value];
    
    if(denominations[numDenominations - 1] <= value){
        return dp[numDenominations][value] = helper(denominations, numDenominations, value - denominations[numDenominations - 1], dp) + helper(denominations, numDenominations - 1, value, dp);
    }
    else
        return dp[numDenominations][value] = helper(denominations, numDenominations - 1, value, dp);
}
int countWaysToMakeChange(int denominations[], int numDenominations, int value){
    int**dp = new int*[numDenominations + 1];
    for(int i=0; i<=numDenominations; i++){
        dp[i] = new int[value + 1];
        for(int j = 0; j <= value; j++)
            dp[i][j] = -1;
    }
    return helper(denominations, numDenominations, value, dp);
}

// DP
int countWaysToMakeChange(int denominations[], int numDenominations, int value){
    int**dp = new int*[numDenominations + 1];
    for(int i=0; i<=numDenominations; i++){
        dp[i] = new int[value + 1];
    }
    for(int i=0; i<=numDenominations; i++)
        dp[i][0] = 1;
    for(int j=0; j<=value; j++)
        dp[0][j] = 0;
    
    for(int i=1; i<=numDenominations; i++){
        for(int j=1; j<=value; j++){
            if(denominations[i-1] <= j)
                dp[i][j] = dp[i][j - denominations[i-1]] + dp[i-1][j];
            else
                dp[i][j] = dp[i-1][j];
        }
    }
    return dp[numDenominations][value];
}