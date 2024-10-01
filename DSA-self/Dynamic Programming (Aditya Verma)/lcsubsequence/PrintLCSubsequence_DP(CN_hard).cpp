/**
 * Print Longest Common Subsequence
 * --------------------------------
 * You are given two strings ‘s1’ and ‘s2’.
 * Return the longest common subsequence of these strings.
 * If there’s no such string, return an empty string. 
 * If there are multiple possible answers, return any such string.
 * 
 * Expected Time Complexity:
 * Try to solve this in O(n*m). Where ‘n’ is the length of ‘s1’ and ‘m’ is the length of ‘s2’. 
 * 
 * Constraints:
 * 1 <= n, m <= 10^3
 * 
 * Time Limit: 1 sec
 */

/*
    NOTE: 
        While including char in ans, comparison of character in strings is RIGHT and preferrable.
        Using the logic that dp[i][j] == 1+dp[i-1][j-1] and moving i--, j-- is WRONG
    eg. s1=xe, s2=xed
            0  x  e  d
    dp = 0 [0, 0, 0, 0]
         x [0, 1, 1, 1]
         e [0, 1, 2, 2]
*/ 

// link: https://www.naukri.com/code360/problems/print-longest-common-subsequence_8416383
// article: https://www.geeksforgeeks.org/printing-longest-common-subsequence/

// Solution: Bottom-up: O(n*m), O(n*m)
string findLCS(int n, int m,string &s1, string &s2){
	vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));
	for(int posi=1; posi<=n; posi++){
		for(int posj=1; posj<=m; posj++){
			if(s1[posi - 1] == s2[posj - 1]){
				dp[posi][posj] = 1 + dp[posi-1][posj-1];
			}
			else {
				dp[posi][posj] = max(dp[posi][posj - 1], dp[posi-1][posj]);
			}
		}
	}
    //can add a check if dp[n][m] = 0 then return "". Otherwise it will be handled below
	int posi = n, posj = m;
	string ans = "";
	while(posi>0 && posj>0){
		if(s1[posi - 1] == s2[posj - 1]){
			ans += s1[posi - 1];
			posi--; posj--;
		} else{
			if(dp[posi][posj - 1] > dp[posi - 1][posj])
				posj--;
			else
				posi--;
		}
	}
	reverse(ans.begin(), ans.end());
	return ans;
}

// Old code
#include <bits/stdc++.h>
using namespace std;
int t[1001][1001];
void lcs(string s1, string s2, int n, int m)
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
}
string printlcs(string s1, string s2)
{
    lcs(s1, s2, s1.length(), s2.length());
    int i = s1.length(), j = s2.length();

    string ans = "";
    while (i > 0 && j > 0)
    {
        // if (t[i][j] == t[i - 1][j - 1] + 1) // IMP: this check is WRONG eg. xed, xe => ans can be "xd"
        if (s1[i - 1] == s2[j - 1])
        {
            ans.push_back(s1[i - 1]);
            i--;
            j--;
        }
        else
        {
            /* recursion method's snippet
                string x = helper(s1, s2, n-1, m);
                string y = helper(s1, s2, n, m-1);
                return x.length() > y.length() ? x : y;
            */
            // At equality we prefer to take y ie. [i][j-1], 
            // so, in below code by putting equality, we can guarantee answer from both methods will come same 
            // -->-- "abcdfae", for s1 = "abcdefacde", s2 = "abcdferaed";
            if (t[i][j - 1] >= t[i - 1][j])
                j--;
            else
                i--;
        }
    }
    reverse(ans.begin(), ans.end());
    return ans;
}
int main()
{
    string s1 = "abcdefacde", s2 = "abcdferaed";
    // getline(cin, s1);
    // getline(cin, s2);
    cout << printlcs(s1, s2) << endl;
}