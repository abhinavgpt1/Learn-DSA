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
*/

// Solution 1: Bottom-up: O(n*m), O(m)
class Solution{
    public:
    int longestCommonSubsequence(string s, string t) {
        int m = s.length(), n = t.length();
        vector<int> dp(n + 1, 0);
        for (int i = 1; i <= m; ++i) {
            int prev = dp[0]; //imp. since dp[i-1][j-1] is not same as dp[i][j-1] (think in terms of 2D dp soln. how updation actually happens)
            for (int j = 1; j <= n; ++j) {
                int temp = dp[j];
                if (s[i - 1] == t[j - 1])
                    dp[j] = 1 + prev;
                else
                    dp[j] = max(dp[j - 1], dp[j]); //IMP. max(prev, dp[j]) is WRONG
                prev = temp;
            }
        }
        // since dp[j] is changing again and again, same S(n)=O(m) isn't possible in memoization. Even O(2*m) isn't possible since O(m+n) states will be in call stack which will require O(m*n) dp size
        return dp[n];
};

// Solution 2: Bottom-up: O(n*m), O(2*m)
class Solution {
public:
    // S(n) can be O(2*min(n,m)) if we fix s1 as smaller string among s1,s2
    int longestCommonSubsequence(string s, string t) {
        int n = s.length(), m = t.length();
        vector<int> prev(m+1, 0), curr(m+1, 0);
        for(int posi=1; posi<=n; posi++){
            for(int posj=1; posj<=m; posj++){
                if(s[posi - 1] == t[posj - 1])
                    curr[posj] = 1 + prev[posj-1];
                else
                    curr[posj] = max(prev[posj], curr[posj-1]);
            }
            prev = curr;
        }
        return curr[m];
    }
};

// Solution 3: Bottom-up: O(n*m), O(n*m)
class Solution{
    public:
    int lcs(int n, int m, string s1, string s2)
    {
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        // base case solved already: lcs when one of the string is 0
        for(int posi=1; posi<=n; posi++){
            for(int posj=1; posj<=m; posj++){
                if(s1[posi-1] == s2[posj-1])
                    dp[posi][posj] = 1 + dp[posi-1][posj-1];
                else
                    dp[posi][posj] = max(dp[posi-1][posj], dp[posi][posj-1]);
            }
        }
        return dp[n][m];
    }
};

// Old code: O(n*m), O(n*m)
#include <bits/stdc++.h>
using namespace std;
int t[1001][1001];
int helper(string s1, string s2, int n, int m)
{
    memset(t, 0, sizeof(t));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                t[i][j] = 1 + t[i - 1][j - 1];
            else
                t[i][j] = max(t[i - 1][j], t[i][j - 1]);
        }
    }
    return t[n][m];
}
int lcs(string s1, string s2)
{
    return helper(s1, s2, s1.length(), s2.length());
}
int main()
{
    string s1 = "abcdefacde", s2 = "abcdferaed";
    // getline(cin, s1);
    // getline(cin, s2);
    cout << lcs(s1, s2) << endl;
}

/*
similar problem - lc substring
|
-->soln. - as soon as chars don't match return 0
         - in dp - put t[i][j] = 0 straightaway