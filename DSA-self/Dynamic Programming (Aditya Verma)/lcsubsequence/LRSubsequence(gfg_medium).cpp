/**
 * Longest Repeating Subsequence
 * -----------------------------
 * Given string str, find the length of the longest repeating subsequence such that it can be found twice in the given string.
 * The two identified subsequences A and B can use the same ith character from string str if and only if that ith character has different indices in A and B. 
 * For example, 
 *      A = "xax" and B = "xax" then the index of first "x" must be different in the original string for A and B.
 * 
 * Expected Time Complexity: O(n^2)
 * Expected Space Complexity: O(n^2)
 * 
 * 
 * Constraints:
 * 1 <= |str| <= 10^3
 */

// link: https://www.geeksforgeeks.org/problems/longest-repeating-subsequence2004/1
// article: https://www.geeksforgeeks.org/longest-repeating-subsequence/

// Solution 1: Bottom-up: O(n^2), O(n)
class Solution {
public:
	// using 1D space approach from LCSubsequence_DP(leetcode_medium).cpp
	int LongestRepeatingSubsequence(string str){
	    int n = str.length();
	    vector<int> dp(n+1, 0);
	    for(int posi=1; posi<=n; posi++){
	        int prev = dp[0];
	        for(int posj=1; posj<=n; posj++){
	            int store = dp[posj];
	            if(str[posi - 1] == str[posj - 1] && posi != posj)
	                dp[posj] = 1 + prev;
	            else
	                dp[posj] = max(dp[posj], dp[posj - 1]);
	            
	            prev = store;
	        }
	    }
	    return dp[n];
	}
};

// Solution 2: Bottom-up: O(n^2), O(n^2)
class Solution{
    public:
	int LongestRepeatingSubsequence(string str){
	    int n = str.length();
	    // NOTE: lcs(str, str) will give str i.e. ans = n which is incorrect
	    vector<vector<int>> dp(n + 1, vector<int>(n + 1, 0));
	    for(int posi=1; posi<=n; posi++){
	        for(int posj=1; posj<=n; posj++){
	           // if(i == j) // WRONG to put this blindly
	           //     continue;
	           if(str[posi - 1] == str[posj - 1] && posi != posj){
	               dp[posi][posj] = 1 + dp[posi-1][posj-1];
	           }
	           else {
	               dp[posi][posj] = max(dp[posi][posj - 1], dp[posi-1][posj]);
	           }
	        }
	    }
	    return dp[n][n];
	}
};

// Solution 3: Memoization: TLE: intuitive approach -> O(n*n), O(n*n) + stack space(O(n))
class Solution {
    int helper(string s, int i, int n, string t, int j, int m, vector<vector<int>> &dp){
        if(i == n || j == m)
            return 0;
        if(dp[i][j] != -1)
            return dp[i][j];
        
        if(s[i] == t[j] && i!=j)
            return dp[i][j] = 1 + helper(s, i+1, n, t, j+1, m, dp);
        else
            return dp[i][j] = max(helper(s, i+1, n, t, j, m, dp), helper(s, i, n, t, j+1, m, dp));
        
    }
	public:
		int LongestRepeatingSubsequence(string str){
		    int n = str.length();
		    vector<vector<int>> dp(n, vector<int>(n, -1));
		    return helper(str, 0, n, str, 0, n, dp);
		}

};