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