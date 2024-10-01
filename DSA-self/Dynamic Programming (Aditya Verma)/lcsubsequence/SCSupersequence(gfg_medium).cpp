/**
 * Shortest Common Supersequence
 * -----------------------------
 * Given two strings X and Y of lengths m and n respectively, find the length of the smallest string which has both, X and Y as its sub-sequences.
 * Note: X and Y can have both uppercase and lowercase letters.
 * 
 * Expected Time Complexity: O(Length(X) * Length(Y)).
 * Expected Auxiliary Space: O(Length(X) * Length(Y)).
 * 
 * Constraints:
 * 1<= |X|, |Y| <= 100
 */

// link: https://www.geeksforgeeks.org/problems/shortest-common-supersequence0322/1
// article: https://www.geeksforgeeks.org/shortest-common-supersequence/

// Solution 1: Bottom-up: intuitve: O(n*m), O(n)
class Solution {
    // this can be optimized to 1D space array soln. - LCSubsequence_DP(leetcode_medium).cpp
public:
    int shortestCommonSupersequence(string X, string Y, int m, int n) {
        vector<int> prev(n+1, 0), dp(n+1, 0);
        for(int j=0; j<=n; j++)
            prev[j] = j;
        
        for(int posi=1; posi<=m; posi++){
            dp[0] = posi; // IMP. since next row has 0th element intialized as length of string X
            for(int posj=1; posj<=n; posj++){
                if(X[posi - 1] == Y[posj - 1])
                    dp[posj] = 1 + prev[posj-1];
                else
                    dp[posj] = 1 + min(prev[posj], dp[posj-1]);
            }
            prev = dp;
        }
        return dp[n];
    }
};

// Solution 2: Bottom-up: intuitve: O(n*m), O(n*m)
class Solution{
    public:
    int shortestCommonSupersequence(string X, string Y, int m, int n) {
        vector<vector<int>> dp(m+1, vector<int>(n+1, 0));
        for(int i=0; i<=m; i++)
            dp[i][0] = i;
        for(int j=0; j<=n; j++)
            dp[0][j] = j;
        
        for(int posi=1; posi<=m; posi++){
            for(int posj=1; posj<=n; posj++){
                if(X[posi - 1] == Y[posj - 1])
                    dp[posi][posj] = 1 + dp[posi-1][posj-1];
                else
                    dp[posi][posj] = 1 + min(dp[posi-1][posj], dp[posi][posj-1]);
            }
        }
        return dp[m][n];
    }
};
// Solution 3: Memoization: intuitve: O(n*m), O(n*m) + stack space(O(m+n))
class Solution{
    int helper(string s, int i, int m, string t, int j, int n, vector<vector<int>> &dp){
        if(i == m || j == n)
            return (m-i) + (n-j);
        
        if(dp[i][j] != -1)
            return dp[i][j];
        
        if(s[i] == t[j])
            return dp[i][j] = 1+helper(s, i+1, m, t, j+1, n, dp);
        else
            return dp[i][j] = 1+min(helper(s, i+1, m, t, j, n, dp), helper(s, i, m, t, j+1, n, dp));
    }
    public:
    int shortestCommonSupersequence(string X, string Y, int m, int n) {
        vector<vector<int>> dp(m, vector<int>(n, -1));
        return helper(X, 0, m, Y, 0, n, dp);
    }
};
/*
    ans = (s1 - lcs) + (s2 - lcs) + lcs => n+m-lcs
*/ 
// Solution 4: Bottom-up: O(n^2), O(n^2)
class Solution{
    public:
    // also refer 1D array approach in LCSubsequence_DP(leetcode_medium).cpp to find lcs
    int shortestCommonSupersequence(string s1, string s2, int n, int m)
    {
        // ans = (s1 - lcs) + (s2 - lcs) + lcs
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        for(int posi=1; posi<=n; posi++){
            for(int posj=1; posj<=m; posj++){
                if(s1[posi-1] == s2[posj-1])
                    dp[posi][posj] = 1 + dp[posi-1][posj-1];
                else
                    dp[posi][posj] = max(dp[posi-1][posj], dp[posi][posj-1]);
            }
        }
        return n + m - dp[n][m];
    }
};