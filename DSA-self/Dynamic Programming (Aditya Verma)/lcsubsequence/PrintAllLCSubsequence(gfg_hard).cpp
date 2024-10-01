/**
 * Print all LCS sequences
 * -----------------------
 * You are given two strings s and t. 
 * Now your task is to print all longest common sub-sequences in lexicographical order.
 * 
 * Note -  A Sub-sequence is derived from another string by deleting some or none of the elements without changing the order of the remaining elements.
 * 
 * Expected Time Complexity: O(n^3)
 * Expected Space Complexity: O(k * n) where k is a constant less than n.
 *  
 * Constraints:
 * 1 ≤ Length of both strings ≤ 50
 */

// link: https://www.geeksforgeeks.org/problems/print-all-lcs-sequences3413/0
// leetcode solution: https://leetcode.com/problems/longest-common-subsequence/solutions/2638427/C++-DP-solution-or-with-Printing-all-LCS-without-TLE/
// article (non-intuitive): https://www.geeksforgeeks.org/print-longest-common-sub-sequences-lexicographical-order/

// Solution 1: Bottom-up: LCS + String generation in bottom-up fashion: O(n*m*s) where s=max subsequences=2^n, O(n*m*s)
class Solution{
    public:
	vector<string> all_longest_common_subsequences(string s, string t)
	{
	    int n = s.length(), m = t.length();
	    vector<vector<set<string>>> dp(n+1, vector<set<string>>(m+1));
	    emptyset.insert("");
	    for(int i=0; i<n+1; i++)
	        dp[i][0].insert("");

	    for(int i=0; i<m+1; i++)
	        dp[0][i].insert("");

	    // storing the strings as well instead of just storing max lcs length at the point [posi][posj]
        for(int posi=1; posi<=n; posi++){
            for(int posj=1; posj<=m; posj++){
                if(s[posi-1] == t[posj-1]){
                    for(string x: dp[posi-1][posj-1])
                        dp[posi][posj].insert(x + s[posi-1]);
                } else{
                    int i_j_minus_1 = dp[posi][posj-1].begin()->length();
                    int i_minus_1_j = dp[posi-1][posj].begin()->length();
                    if(i_j_minus_1 > i_minus_1_j)
                        dp[posi][posj] = dp[posi][posj-1];
                    else if(i_j_minus_1 < i_minus_1_j)
                        dp[posi][posj] = dp[posi-1][posj];
                    else{
                        for(string x: dp[posi][posj-1])
                            dp[posi][posj].insert(x);
                        for(string x: dp[posi-1][posj])
                            dp[posi][posj].insert(x);
                    }
                }
            }
        }
        // No need for checking whole list where dp[i][j] = lcslen (since we are accumulating all possible strings of length L)
        
        // int lcslen = dp[n][m].begin()->length(); // this value can be anywhere hanging in the matrix, and at multiple places
        // if(lcslen == 0)
        //     return {""};
        // set<string> lcsstrings;
        // for(int posi=1; posi<=n; posi++){
        //     for(int posj=1; posj<=m; posj++){
        //         if(dp[posi][posj].begin()->length() == lcslen){
        //             for(string x: dp[posi][posj]){
        //                 lcsstrings.insert(x);
        //             }
        //         }
        //     }
        // }
        // vector<string> ans(lcsstrings.begin(), lcsstrings.end());
        vector<string> ans(dp[n][m].begin(), dp[n][m].end());
        return ans;
	}
};

// Solution 2: Recursive after LCS calc: TLE : O(n*m) + 2^min(m,n), O(n*m)
class Solution{
    set<string> getlcs(vector<vector<int>> &dp, string s, string t, int posi, int posj){
        string ans = "";
        while(posi > 0 && posj > 0){
            if(s[posi - 1] == t[posj - 1])
            {
                ans += s[posi - 1];
                posi--; posj--;
            } else{
                if(dp[posi][posj - 1] > dp[posi - 1][posj])
                    posj--;
                else if(dp[posi][posj - 1] < dp[posi - 1][posj])
                    posi--;
                else{
                    // recursive call in both directions
                    set<string> tmp1 = getlcs(dp, s, t, posi - 1, posj);
                    set<string> tmp2 = getlcs(dp, s, t, posi, posj - 1);
                    set<string> newans;
                    
                    for(string y1: tmp1){
                        newans.insert(ans + y1);
                    }
                    for(string y2: tmp2){
                        newans.insert(ans + y2);
                    }
                    return newans;
                }
            }
        }
        set<string> aa;
        aa.insert(ans);
        return aa;
    }
	public:
	vector<string> all_longest_common_subsequences(string s, string t)
	{
	    int n = s.length(), m = t.length();
	    vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        // base case for lcs solved already
        for(int posi=1; posi<=n; posi++){
            for(int posj=1; posj<=m; posj++){
                if(s[posi-1] == t[posj-1])
                    dp[posi][posj] = 1 + dp[posi-1][posj-1];
                else
                    dp[posi][posj] = max(dp[posi-1][posj], dp[posi][posj-1]);
            }
        }
        int lcslen = dp[n][m]; // this value can be anywhere hanging in the matrix, and at multiple places
        if(lcslen == 0)
            return {""};
        
        // O(N+M) = complexity to form a single lcs
        set<string> lcsstrings;
        for(int posi=1; posi<=n; posi++){
            for(int posj=1; posj<=m; posj++){
                if(dp[posi][posj] == lcslen){
                    for(string x: getlcs(dp, s, t, posi, posj)){
                        reverse(x.begin(), x.end());
                        lcsstrings.insert(x);
                    }
                }
            }
        }
        vector<string> ans(lcsstrings.begin(), lcsstrings.end());
        return ans;
	}
};