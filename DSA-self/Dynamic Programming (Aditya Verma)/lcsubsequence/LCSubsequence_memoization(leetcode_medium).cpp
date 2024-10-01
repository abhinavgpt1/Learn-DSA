/**
 * 1143. Longest Common Subsequence
 * --------------------------------
 * Given two strings text1 and text2, return the length of their longest common subsequence.
 * If there is no common subsequence, return 0.
 * A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
 * For example, "ace" is a subsequence of "abcde".
 * A common subsequence of two strings is a subsequence that is common to both strings.
 * 
 * Constraints:
 * 1 <= text1.length, text2.length <= 1000
 * text1 and text2 consist of only lowercase English characters.
 */

// link: https://leetcode.com/problems/longest-common-subsequence/description/
// link: https://www.geeksforgeeks.org/problems/longest-common-subsequence-1587115620/1
// article: https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
// article: https://www.geeksforgeeks.org/space-optimized-solution-lcs/

/*
    Application of LCS:
    - To implement diff utility i.e. find the difference between two data sources
    - Revision control systems such as Git for multiple changes made to a revision-controlled collection of files. 

    Memoization approach gives TLE on gfg, but DP doesn't
*/ 

// Solution: Memoization (top-down): O(n*m), O(n*m) + O(m+n) [stack space]
class Solution {
    int lcshelper(int n, int m, string s1, string s2, vector<vector<int>> &dp){
        if(n == 0 || m == 0) // lcs when one of the string is 0
            return 0;
        if(dp[n][m] != -1)
            return dp[n][m];
        if(s1[n-1] == s2[m-1]){
            return dp[n][m] = 1 + lcshelper(n-1, m-1, s1, s2, dp);
        } else {
            return dp[n][m] = max(lcshelper(n-1, m, s1, s2, dp), lcshelper(n, m-1, s1, s2, dp));
        }
    }
    public:
    //Function to find the length of longest common subsequence in two strings.
    int lcs(int n, int m, string s1, string s2)
    {
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        return lcshelper(n, m, s1, s2, dp);
    }
};

// Old 
#include <bits/stdc++.h>
using namespace std;
int t[1001][1001];
int helper(string s1, string s2, int n, int m)
{
    if (n == 0 || m == 0)
        return 0;
    if (t[n][m] != -1)
        return t[n][m];
        
    if (s1[n - 1] == s2[m - 1])
        return t[n][m] = helper(s1, s2, n - 1, m - 1) + 1;
    else
        return t[n][m] = max(helper(s1, s2, n - 1, m), helper(s1, s2, n, m - 1));
}
int lcs(string s1, string s2)
{
    return helper(s1, s2, s1.length(), s2.length());
}
int main()
{
    memset(t, -1, sizeof(t));
    string s1 = "abcdefacde", s2 = "abcdferaed";
    // getline(cin, s1);
    // getline(cin, s2);
    cout << lcs(s1, s2) << endl;
}