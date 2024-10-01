/**
 * Minimum number of deletions
 * ---------------------------
 * Given a string 'str' of size ‘n’. 
 * The task is to remove or delete the minimum number of characters from the string so that the resultant string is a palindrome. 
 * Find the minimum numbers of characters we need to remove.
 * Note: The order of characters should be maintained.
 *
 * Expected Time Complexity: O(|str|^2)
 * Expected Auxiliary Space: O(|str|^2)
 * 
 * Constraints:
 * 1 ≤ |str| ≤ 10^3
 */

// link: https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/description/
// link: https://www.geeksforgeeks.org/problems/minimum-number-of-deletions4610/1
// link: https://www.geeksforgeeks.org/problems/form-a-palindrome2544/1
// article: https://www.geeksforgeeks.org/minimum-number-deletions-make-string-palindrome/

/*
    PTR: min deletions = min insertions
*/

// Solution 1: generate substrings right to left, and use logic as in memoization (solution 3 below)

// Solution 2: Bottom-up: LPS on s, reverse(s) -> O(n*n), O(n*n)
class Solution {
    // refer 1D solution in LPSubsequence_DP(gfg_medium)
    public:
    int minDeletions(string A, int n)
    {
        // Min. deletion implies longest palindrome
        // This can easily found with Longest Palindrome Subsequence
        // qq: why subsequence -> ans: post char deletion subsequence will result in palindromic string

        // ANS = n - longest palindrome subsequence length = n - lcs(A, reverse(A))
        string s1 = A, s2 = A;
        reverse(s2.begin(), s2.end());
        vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
        for (int posi = 1; posi <= n; posi++)
        {
            for (int posj = 1; posj <= n; posj++)
            {
                if (s1[posi - 1] == s2[posj - 1])
                    dp[posi][posj] = 1 + dp[posi - 1][posj - 1];
                else
                    dp[posi][posj] = max(dp[posi - 1][posj], dp[posi][posj - 1]);
            }
        }
        return n - dp[n][n];
    }
};

// Solution 3: Memoization: TLE -> O(n*n), O(n*n)
// recursive solution has O(2^n), O(n) [stack space] complexities
int helper(string s, int start, int end, vector<vector<int>> &dp){
    if(start >= end)
        return 0;
    if(dp[start][end] != -1)
        return dp[start][end];
    if(s[start] == s[end])
        return dp[start][end] = helper(s, start + 1, end - 1, dp);
    else
        return dp[start][end] = min(
            1 + helper(s, start + 1, end, dp), //delete from front
            1 + helper(s, start, end - 1, dp) // delete from end
        );
}
int minDeletions(string str, int n) {
    vector<vector<int>> dp(n, vector<int>(n, -1));
    return helper(str, 0, n-1, dp);
} 