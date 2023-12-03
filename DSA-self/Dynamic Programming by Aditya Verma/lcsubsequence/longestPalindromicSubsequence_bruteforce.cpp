#include <bits/stdc++.h>
using namespace std;

// soln. on leetcode
int longestPalindromeSubseq(string s)
{
    return longestPalindromeSubseq(0, s.size() - 1, s);
}
int longestPalindromeSubseq(int l, int r, string &s)
{
    if (l == r)
        return 1;
    if (l > r)
        return 0; // happens after "aa"
    return s[l] == s[r] ? 2 + longestPalindromeSubseq(l + 1, r - 1, s) : max(longestPalindromeSubseq(l + 1, r, s), longestPalindromeSubseq(l, r - 1, s));
}

int main()
{
    string s = "abcdefacde";
    // getline(cin, s);
    cout << lps(s) << endl;
}
// basic soln. - lcs on s, reverse(s)