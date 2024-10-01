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

// Solution: Recursive: O(2^(N+M)) [since all subsequences are made], O(1) + stack space O(n+m)
#include <bits/stdc++.h>
using namespace std;

string helper(string s1, string s2, int n, int m)
{
    if(n == 0 || m == 0)
    return "";

    if(s1[n-1] == s2[m-1])
    return helper(s1, s2, n-1, m-1) + s1[n-1];
    else
    {
        string x = helper(s1, s2, n-1, m);
        string y = helper(s1, s2, n, m-1);
        return x.length() > y.length() ? x : y;
    }
}
string printlcs(string s1, string s2)
{
    return helper(s1, s2, s1.length(), s2.length());
}
int main()
{
    string s1 = "abcdefacde", s2 = "abcdferaed";
    // getline(cin, s1);
    // getline(cin, s2);
    cout << printlcs(s1, s2) << endl;
}
