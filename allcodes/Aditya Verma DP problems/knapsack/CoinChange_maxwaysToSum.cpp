/*
Coin Change 
Medium Accuracy: 47.19% Submissions: 66505 Points: 4
Given a value N, find the number of ways to make change for N cents, if we have infinite supply of each of S = { S1, S2, .. , SM } valued coins.


Example 1:

Input:
n = 4 , m = 3
S[] = {1,2,3}
Output: 4
Explanation: Four Possible ways are:
{1,1,1,1},{1,1,2},{2,2},{1,3}.
Example 2:

Input:
n = 10 , m = 4
S[] ={2,5,3,6}
Output: 5
Explanation: Five Possible ways are:
{2,2,2,2,2}, {2,2,3,3}, {2,2,6}, {2,3,5} 
and {5,5}.

Your Task:
You don't need to read input or print anything. Your task is to complete the function count() which accepts an array S[] its size m and n as input parameter and returns the number of ways to make change for N cents.


Expected Time Complexity: O(m*n).
Expected Auxiliary Space: O(n).


Constraints:
1 <= n,m <= 103
*/

// unbounded = countSubsetSum

// memoized
class Solution
{
public:
    long long int t[1001][1001];
    Solution(){
        memset(t, -1, sizeof(t));
    }
    long long int count(int S[], int m, int n){
        if (n == 0)
            return 1;
        if (m == 0)
            return 0;

        if (t[m][n] != -1)
            return t[m][n];

        if (S[m - 1] <= n)
            return t[m][n] = count(S, m - 1, n) + count(S, m, n - S[m - 1]);
        else
            return t[m][n] = count(S, m - 1, n);
    }
};

// DP
class Solution{
  public:
    long long int t[1001][1001];
    long long int count(int S[], int m, int n) {

        memset(t, 0, sizeof(t));
        for(int i=0; i<m; i++)
        t[i][0] = 1;
        
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(S[i-1] <= j)
                t[i][j] = t[i][j-S[i-1]] + t[i-1][j];
                else
                t[i][j] = t[i-1][j];;
            }
        }
        return t[m][n];
    }
};
