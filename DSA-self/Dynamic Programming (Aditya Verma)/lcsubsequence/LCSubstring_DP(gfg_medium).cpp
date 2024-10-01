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

// Solution: Bottom-up: O(m*n), O(m)
class Solution {
    // 1d dp array soln. inspired from LCSubsequence_DP(leetcode_medium).cpp
    // two 1d array soln. is always available
    public:
    int longestCommonSubstr(string str1, string str2) {
        int n = str1.length(), m = str2.length(), ans = 0;
        vector<int> dp(m+1, 0);
        for(int posi=1; posi<=n; posi++){
            int prev = dp[0];
            for(int posj=1; posj<=m; posj++){
                int store = dp[posj];
                
                if(str1[posi - 1] == str2[posj - 1])
                    dp[posj] = 1 + prev;
                else
                    dp[posj] = 0; // this needs to be done. Can't rely on dp initialization. It works only if we have 2D dp
                
                prev = store;
                ans = max(ans, dp[posj]);
            }
        }
        return ans;
    }
};

// Solution: Bottom-up: O(m*n), O(m*n)
class Solution
{
public:
    int longestCommonSubstr(string s1, string s2, int n, int m)
    {
        int ans = 0;
        vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
        for (int posi = 1; posi <= n; posi++)
        {
            for (int posj = 1; posj <= m; posj++)
            {
                if (s1[posi - 1] == s2[posj - 1])
                {
                    dp[posi][posj] = 1 + dp[posi - 1][posj - 1];
                    ans = max(ans, dp[posi][posj]);
                }
                // else // redundant due to initalization
                //     dp[posi][posj] = 0;
            }
        }
        return ans;
    }
};