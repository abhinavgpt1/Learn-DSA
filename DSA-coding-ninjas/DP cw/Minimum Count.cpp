/*
Code : Minimum Count
Send Feedback
Given an integer N, find and return the count of minimum numbers required to represent N as a sum of squares.
That is, if N is 4, then we can represent it as : {1^2 + 1^2 + 1^2 + 1^2} and {2^2}. The output will be 1, as 1 is the minimum count of numbers required to represent N as sum of squares.
Input format :
The first and the only line of input contains an integer value, 'N'.
 Output format :
Print the minimum count of numbers required.
Constraints :
0 <= n <= 10 ^ 4

Time Limit: 1 sec
Sample Input 1 :
12
Sample Output 1 :
3
Explanation of Sample Output 1 :
12 can be represented as : 
A) (1^1) + (1^1) + (1^1) + (1^1) + (1^1) + (1^1) + (1^1) + (1^1) + (1^1) + (1^1) + (1^1) + (1^1)

B) (1^1) + (1^1) + (1^1) + (1^1) + (1^1) + (1^1) + (1^1) + (1^1)  + (2 ^ 2)

C) (1^1) + (1^1) + (1^1) + (1^1) + (2 ^ 2) + (2 ^ 2)

D) (2 ^ 2) + (2 ^ 2) + (2 ^ 2)

As we can see, the output should be 3.
Sample Input 2 :
9
Sample Output 2 :
1
*/

#include<climits>
int minCount(int n)
{
    int *dp = new int[n + 1];
    for(int i=0; i<n+1; i++)
        dp[i] = INT_MAX;
    dp[0] = dp[1] = 1; dp[2] = 2;
    
    for(int i=3; i<n+1; i++){
        int root = sqrt(i);
        if(root * root == i)
            dp[i] = 1;
        else{
            int minVal = INT_MAX;
            for(int j = 1; j <= root; j++)
                minVal = min(minVal, dp[i - j*j] + 1);
            dp[i] = minVal;
        }
    }
    return dp[n];
}

//using DP
#include<cmath>
int minCount(int n)
{
	//Write your code here
	
    //     fails at n = 0 : ans = 1 but by default dp[0] = 0
    int * dp = new int[n+1]();
    dp[1] = 1;
    for(int i = 2; i <= n; i++){
        int sroot = sqrt(n);
        int min = i;
        for(int j = 1; j <= sroot; j++){
            int localAns = 1;
            localAns += dp[i - j*j];
            
            if(localAns < min)
                min = localAns;
        }
        dp[i] = min;
    }
    return dp[n];
}

/*
#include<cmath>
int minCount(int n, int * dp)
{
	//Write your code here
    if(dp[n] != -1)
        return dp[n];
    
    int sroot = sqrt(n);
    int min = n;//1^2 + 1^2 +... ntimes
    for(int i = 1; i <= sroot; i++){
        int localAns = 1;//i.e. 1^2 , 2^2, 3^3
        localAns += minCount(n - i*i, dp);
        if(localAns < min)
            min = localAns;
    }
    return dp[n] = min;
}
int minCount(int n)
{
    int * dp = new int[n + 1];    
    dp[0] = 0;
    for(int i = 1; i <= n; i++)
        dp[i] = -1;
    return minCount(n, dp);
}
*/
/*
//recursive
#include<cmath>
int minCount(int n)
{
	//Write your code here
    int sroot = sqrt(n);
    int min = n;//1^2 + 1^2 +... ntimes
    for(int i = 1; i <= sroot; i++){
        int localAns = 1;//i.e. 1^2 , 2^2, 3^3
        localAns += minCount(n - i*i);
        if(localAns < min)
            min = localAns;
    }
    return min;
}
*/