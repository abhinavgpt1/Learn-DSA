/**
 * Longest Common Substring
 * ------------------------
 * You are given two strings str1 and str2. 
 * Your task is to find the length of the longest common substring among the given strings.
 *
 * Expected Time Complexity: O(n*m).
 * Expected Auxiliary Space: O(n*m).
 * 
 * Constraints:
 * 1<= str1.size(), str2.size()<=1000
 * Both strings may contain upper and lower case alphabets.
 *
 */

// link: https://www.geeksforgeeks.org/problems/longest-common-substring1452/1
// similar problem link: https://leetcode.com/problems/maximum-length-of-repeated-subarray/description/
// article: https://www.geeksforgeeks.org/longest-common-substring-dp-29/


// Solution: Memoization: O(n*m), O(n*m) + stack space[O(min(m,n))]
class Solution {
    int helper(const string &str1, const string &str2, vector<vector<int>> &dp, int idx1, int idx2) {
        if(idx1 == str1.length() || idx2 == str2.length())
            return 0;
        if(dp[idx1][idx2] != -1)
            return dp[idx1][idx2];

        if(str1[idx1] == str2[idx2])
            return dp[idx1][idx2] = 1 + helper(str1, str2, dp, idx1+1, idx2+1);
        return dp[idx1][idx2] = 0;
    }
  public:
    int longestCommonSubstr(string str1, string str2) {
        // brute force logic for LCS is not same here
        // dp[i][j] stores lcsubstring for str1[0...i], str2[0...j] => ans != dp[n-1][m-1]
        int n = str1.length(), m = str2.length(), ans = 0;
        vector<vector<int>> dp(n+1, vector<int>(m+1, -1));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(str1[i] == str2[j])
                    ans = max(ans, helper(str1, str2, dp, i, j));
            }
        }
        return ans;
    }
}

// old code - fails due to TLE on gfg
class Solution
{
public:
    int getCommonSubstringLength(string s1, string s2, int i, int j, int n, int m, vector<vector<int>> &dp)
    {
        int x = i + 1, y = j + 1;
        int len = 0;
        while (i < n && j < m)
        {
            if (dp[i + 1][j + 1] != -1)
                return dp[x][y] = dp[i + 1][j + 1] + len;

            if (s1[i] == s2[j])
            {
                len++;
                i++;
                j++;
            }
            else
            {
                break;
            }
        }
        return dp[x][y] = len;
    }
    int longestCommonSubstr(string s1, string s2, int n, int m)
    {
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, -1));
        for (int i = 0; i < n + 1; i++)
        {
            dp[i][0] = 0;
        }
        for (int i = 0; i < m + 1; i++)
        {
            dp[0][i] = 0;
        }

        int ans = 0;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (s1[i] == s2[j])
                {
                    int tmp = getCommonSubstringLength(s1, s2, i, j, n, m, dp);
                    ans = max(ans, tmp);
                }
            }
        }
        return ans;
    }
};