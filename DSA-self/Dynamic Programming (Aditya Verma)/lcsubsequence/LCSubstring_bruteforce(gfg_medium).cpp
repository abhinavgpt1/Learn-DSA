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

// Solution: Recursive: O(n*m*min(m,n)), O(min(m,n))
class Solution {
    int helper(const string &str1, const string &str2, int idx1, int idx2) {
        if(idx1 == str1.length() || idx2 == str2.length())
            return 0;
        if(str1[idx1] == str2[idx2])
            return 1 + helper(str1, str2, idx1+1, idx2+1);
        return 0;
    }
  public:
    int longestCommonSubstr(string str1, string str2) {
        // brute force logic for LCS is not same here

        int n = str1.length(), m = str2.length(), ans = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(str1[i] == str2[j])
                    ans = max(ans, helper(str1, str2, i, j));
            }
        }
        return ans;
    }
};

// old code
#include <bits/stdc++.h>
using namespace std;
int getCommonSubstringLength(string s1, string s2, int i, int j, int n, int m)
{
    int len = 0;
    while (i < n && j < m)
    {
        if (s1[i] == s2[j])
        {
            len++;
            i++; j++;
        }
        else
        {
            break;
        }
    }
    return len;
}
int longestCommonSubstr(string s1, string s2, int n, int m)
{
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (s1[i] == s2[j])
            {
                int tmp = getCommonSubstringLength(s1, s2, i, j, n, m);
                ans = max(ans, tmp);
            }
        }
    }
    return ans;
}
int main()
{
    string s1 = "abcdefacde", s2 = "abcdferaed";
    // getline(cin, s1);
    // getline(cin, s2);
    cout << longestCommonSubstr(s1, s2, s1.length(), s2.length()) << endl;
}