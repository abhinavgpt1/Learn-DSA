/**
 * Longest Palindromic Subsequence
 * -------------------------------
 * Given a String, find the longest palindromic subsequence.
 * 
 * Expected Time Complexity: O(|S|*|S|).
 * Expected Auxiliary Space: O(|S|*|S|).
 * 
 * Constraints:
 * 1 ≤ |S| ≤ 1000
 */

// link: https://www.geeksforgeeks.org/problems/longest-palindromic-subsequence-1612327878/1
// link: https://leetcode.com/problems/longest-palindromic-subsequence/description/
// article: https://www.geeksforgeeks.org/longest-palindromic-subsequence-dp-12/

// Solution 1: Memoization: O(2^n), O(n^2) + stack space (O(2n))
class Solution{
    int helper(int l, int r, string &s, vector<vector<int>> &dp)
    {
        if (l == r)
            return 1;
        if (l > r)
            return 0; // happens after "aa"
        
        if(dp[l][r] != -1)
            return dp[l][r];
        
        return dp[l][r] = 
        (
            s[l] == s[r] 
                ? 2 + helper(l+1, r-1, s, dp) 
                : max(helper(l+1, r, s, dp), helper(l, r-1, s, dp))
        );
    }
  public:
    int longestPalinSubseq(string A) {
        vector<vector<int>> dp(A.size(), vector<int>(A.size(), -1));
        return helper(0, A.size() - 1, A, dp);
    }
};

/*
    Note: lpsubsequence === lcsubsequence between s, reverse(s)
*/

// Solution 2: Memoization using basic LCSubsequence_memoization(gfg_medium).cpp technique on A, rev(A)