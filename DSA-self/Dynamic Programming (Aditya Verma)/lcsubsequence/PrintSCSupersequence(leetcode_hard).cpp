/**
 * 1092. Shortest Common Supersequence 
 * -----------------------------------
 * Given two strings str1 and str2, return the shortest string that has both str1 and str2 as subsequences. 
 * If there are multiple valid strings, return any of them.
 * A string s is a subsequence of string t if deleting some number of characters from t (possibly 0) results in the string s.
 * 
 * Constraints:
 * 1 <= str1.length, str2.length <= 1000
 * str1 and str2 consist of lowercase English letters.
 */

// link: https://leetcode.com/problems/shortest-common-supersequence/description/
// article: https://www.geeksforgeeks.org/print-shortest-common-supersequence/

// Both solutions have same procedure to extract the string. The DP creation differs.

// Solution 1: Using LCS - O(n*m) + O(m+n), O(n*m)
class Solution {
public:
    int dp[1001][1001];
    
    void lcs(string s, string t, int m, int n) {
        
        memset(dp, 0, sizeof(dp));
        for(int i=1; i<=m; i++){
            for(int j=1; j<=n; j++){
                if(s[i-1] == t[j-1])
                    dp[i][j] = 1 + dp[i-1][j-1];
                else
                    dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
            }
        }
        
    }
    string shortestCommonSupersequence(string str1, string str2) {
        int m = str1.length();
        int n = str2.length();
        lcs(str1, str2, m, n);
        int i=m, j=n;
        string ans = "";
        while(i>0 && j>0){
            if(str1[i-1] == str2[j-1])
            {
                ans += str1[i-1];
                i--;j--;
            }
            else{
                if(dp[i][j-1] > dp[i-1][j]){
                    ans+=str2[j-1];
                    j--;
                }
                else{
                    ans+=str1[i-1];
                    i--;
                }
            }
        }
        while(i>0){
            ans+=str1[i-1];
            i--;
        }
        while(j>0){
            ans+=str2[j-1];
            j--;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};

// Solution 2: Intuitive way - O(n*m) + O(m+n), O(n*m)
class Solution {
public:
    string shortestCommonSupersequence(string str1, string str2) {
        int n = str1.length();
        int m = str2.length();
        vector<vector<int>> dp(n+1, vector<int>(m+1, 0));
        for(int i=0; i<=n; i++)
            dp[i][0] = i;
        for(int j=0; j<=m; j++)
            dp[0][j] = j;
        
        for(int posi=1; posi<=n; posi++){
            for(int posj=1; posj<=m; posj++){
                if(str1[posi-1] == str2[posj-1])
                    dp[posi][posj] = 1+dp[posi-1][posj-1];
                else
                    dp[posi][posj] = 1+min(dp[posi-1][posj], dp[posi][posj-1]);
            }
        }
        string ans = "";
        int posi=n, posj=m;
        while(posi>0 && posj>0){
            if(str1[posi-1] == str2[posj-1]){
                ans += str1[posi-1];
                posi--; posj--;
            } else if(dp[posi][posj-1] < dp[posi-1][posj]){
                ans += str2[posj-1];
                posj--;
            } else{
                ans += str1[posi-1];
                posi--;
            }
        }
        while(posi > 0)
        {
            ans += str1[posi-1];
            posi--;
        }
        while(posj > 0)
        {
            ans += str2[posj-1];
            posj--;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};