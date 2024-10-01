/**
 * Minimum number of deletions and insertions
 * ------------------------------------------
 * Given two strings str1 and str2.
 * The task is to remove or insert the minimum number of characters from/in str1 so as to transform it into str2.
 * It could be possible that the same character needs to be removed/deleted from one point of str1 and inserted to some another point.
 *
 * Expected Time Complexity: O(|str1|*|str2|)
 * Expected Space Complexity: O(|str1|*|str2|)
 * 
 * Constraints:
 * 1 ≤ |str1|, |str2| ≤ 1000
 * All the characters are lowercase English alphabets
 */

// link: https://www.geeksforgeeks.org/problems/minimum-number-of-deletions-and-insertions0209/1
// link: https://leetcode.com/problems/delete-operation-for-two-strings/description/
// article: https://www.geeksforgeeks.org/minimum-number-deletions-insertions-transform-one-string-another/

// Solution 1: Bottom-up: using LCS -> O(n*m), O(n*m)
class Solution {
    // also refer 1D space solution from LCSubsequence_DP(leetcode_medium).cpp
public:
    int minOperations(string s1, string s2)
    {
        // ans(s1->s2) = remove=(s1 - lcs) + insert=(s2 - lcs)
        int n = s1.length(), m = s2.length();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int posi = 1; posi <= n; posi++)
        {
            for (int posj = 1; posj <= m; posj++)
            {
                if (s1[posi - 1] == s2[posj - 1])
                    dp[posi][posj] = 1 + dp[posi - 1][posj - 1];
                else
                    dp[posi][posj] = max(dp[posi - 1][posj], dp[posi][posj - 1]);
            }
        }
        return n + m - 2 * dp[n][m];
    }
};

// Solution 2: Memoization: Intuitive solution -> O(n*m), O(n*m) + stack space (O(m+n))
class Solution {
    // Same can be done via DP, but LCS approach is better
    int helper(string s, int i, int n, string t, int j, int m, vector<vector<int>> &dp){
        if(i == n || j == m)
            return (n-i)+(m-j); //either insert or delete the remaining characters
        if(dp[i][j] != -1)
            return dp[i][j];
        if(s[i] == t[j])
            return dp[i][j] = helper(s, i+1, n, t, j+1, m, dp);
        else
            return dp[i][j] = min(
                1 + helper(s, i+1, n, t, j, m, dp), //delete char at s[i]
                1 + helper(s, i, n, t, j+1, m, dp) // insert char at s[i] = t[j]
            );
    }
	public:
	int minOperations(string str1, string str2) { 
	    int n = str1.length(), m = str2.length();
	    vector<vector<int>> dp(n, vector<int>(m, -1));
	    return helper(str1, 0, n, str2, 0, m, dp);
	} 
};

/*
    ans(s1 -> s2) = remove(s1 - lcs) + insert(s2 - lcs)
    OR
    ans(s1 == s2) = remove(s1 - lcs) + remove(s2 - lcs)
*/ 
