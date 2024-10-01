/**
 * 1143. Longest Common Subsequence
 * --------------------------------
 * Given two strings text1 and text2, return the length of their longest common subsequence.
 * If there is no common subsequence, return 0.
 * A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.
 * For example, "ace" is a subsequence of "abcde".
 * A common subsequence of two strings is a subsequence that is common to both strings.
 * 
 * Constraints:
 * 1 <= text1.length, text2.length <= 1000
 * text1 and text2 consist of only lowercase English characters.
 */

// link: https://leetcode.com/problems/longest-common-subsequence/description/
// link: https://www.geeksforgeeks.org/problems/longest-common-subsequence-1587115620/1
// article: https://www.geeksforgeeks.org/longest-common-subsequence-dp-4/
// article: https://www.geeksforgeeks.org/space-optimized-solution-lcs/

/*
    Application of LCS:
    - To implement diff utility i.e. find the difference between two data sources
    - Revision control systems such as Git for multiple changes made to a revision-controlled collection of files. 
*/

// Solution: Recursive: O(2^(min(m,n))), O(m+n)
#include <bits/stdc++.h>
using namespace std;

int helper(string s1, string s2, int n, int m)
{
    if (n == 0 || m == 0)
        return 0;
    if (s1[n - 1] == s2[m - 1])
        return helper(s1, s2, n - 1, m - 1) + 1;
    else
        return max(helper(s1, s2, n - 1, m), helper(s1, s2, n, m - 1));
}
int lcs(string s1, string s2)
{
    return helper(s1, s2, s1.length(), s2.length());
}
int main()
{
    string s1 = "abcdefacde", s2 = "abcdferaed";
    // getline(cin, s1);
    // getline(cin, s2);
    cout << lcs(s1, s2) << endl;
}