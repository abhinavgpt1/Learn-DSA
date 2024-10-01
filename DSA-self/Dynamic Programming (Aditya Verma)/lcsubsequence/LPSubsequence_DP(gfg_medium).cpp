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
// article: https://www.geeksforgeeks.org/minimum-number-deletions-make-string-palindrome/#:~:text=of%20%0A//%20the%20longest%20palindromic%20%0A//%20subsequence%20in%20%27str%27-,int%20lps(string%20str),-%7B%0A%20%20%20%20int%20n%20%3D%20str.size()%3B%0A%0A%20%20%20%20//%20Create
// article: https://www.geeksforgeeks.org/longest-palindromic-subsequence-dp-12/

// Solution 1: Bottom-up: Generate all substrings right to left and use logic as in solution 2: O(n^2), O(n)

// Solution 2: Bottom-up: Generate all substrings: O(n^2), O(n^2)
class Solution{
  public:
    int longestPalinSubseq(string s) {
        int n = s.length();
        vector<vector<int>> dp(n, vector<int>(n, 0));
        for(int len=1; len<=n; len++){
            for(int i=0; i<=n-len; i++){
                int firstpossubstring = i;
                int lastpossubstring = i + len - 1;
                if(firstpossubstring == lastpossubstring)
                    dp[firstpossubstring][lastpossubstring] = 1;
                else if(s[firstpossubstring] == s[lastpossubstring])
                    dp[firstpossubstring][lastpossubstring] = 2 + dp[firstpossubstring+1][lastpossubstring-1];
                else
                    dp[firstpossubstring][lastpossubstring] = max(dp[firstpossubstring+1][lastpossubstring], dp[firstpossubstring][lastpossubstring-1]);
            }
        }
        return dp[0][n-1];
    }
    // this CANNOT be optimzied to O(n) space (even with 2 dp arrays of N size)
    // check this technique of creating substrings and dp - https://www.geeksforgeeks.org/longest-palindromic-subsequence-dp-12/#:~:text=n2)-,Using%20Bottom%2Dup%20DP%20(Space%20Optimization),-This%20approach%20optimizes
};

/*
    Note: lpsubsequence === lcsubsequence between s, reverse(s)
*/
// Solution 3: Bottom-up: LCS on A, rev(A) -> O(n*n), O(n)
class Solution{
    int lcs(string s, string t, int n, int m) {
        // inspired from 1D dp soln. at LCSubsequence_DP(leetcode_medium).cpp
        vector<int> dp(m + 1, 0);
        for(int posi=1; posi<=n; posi++){
            int prev = dp[0];
            for(int posj=1; posj<=m; posj++){
                int store = dp[posj];
                
                if(s[posi - 1] == t[posj - 1])
                    dp[posj] = 1 + prev;
                else
                    dp[posj] = max(dp[posj-1], dp[posj]); //comparison between dp[i][j-1] (aka dp[posj-1] != prev) vs dp[i-1][j] (aka dp[posj]) //IMP. max(prev, dp[j]) is WRONG
                
                prev = store;
            }
        }
        return dp[m];
    }
  public:
    int longestPalinSubseq(string A) {
        string revA = A; reverse(revA.begin(), revA.end());
        return lcs(A, revA, A.length(), revA.length());
    }
};

// Solution 4: Bottom-up: LCS on A, rev(A) -> O(n*n), O(n*n)
class Solution{
  public:
    int longestPalinSubseq(string A) {
        // simplifies to finding lcs between A and reverse(A)
        string s1 = A, s2 = A;
        reverse(s2.begin(), s2.end());
        int n = A.length();
        vector<vector<int>> dp(n+1, vector<int>(n+1, 0));
        // base case done already // lcs when one of the string is 0
        for(int posi=1; posi<=n; posi++){
            for(int posj=1; posj<=n; posj++){
                if(s1[posi-1] == s2[posj-1])
                    dp[posi][posj] = 1 + dp[posi-1][posj-1];
                else
                    dp[posi][posj] = max(dp[posi-1][posj], dp[posi][posj-1]);
            }
        }
        return dp[n][n];
    }
};