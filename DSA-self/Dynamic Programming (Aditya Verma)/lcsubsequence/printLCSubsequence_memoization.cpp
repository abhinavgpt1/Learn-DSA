#include <bits/stdc++.h>
using namespace std;

string t[1000][1000];
string helper(string s1, string s2, int n, int m)
{
    if (n == 0 || m == 0)
        return "";
    if(t[n][m] != "zzzzzzzz")
    return t[n][m];
    if (s1[n - 1] == s2[m - 1])
        return t[n][m] = helper(s1, s2, n - 1, m - 1) + s1[n - 1];
    else
    {
        string x = helper(s1, s2, n - 1, m);
        string y = helper(s1, s2, n, m - 1);
        return t[n][m] = (x.length() > y.length() ? x : y);
    }
}
string printlcs(string s1, string s2)
{
    for (int i = 0; i < 1000; i++)
        for (int j = 0; j < 1000; j++)
            t[i][j] = "zzzzzzzz";
    return helper(s1, s2, s1.length(), s2.length());
}
int main()
{
    string s1 = "abcdefacde", s2 = "abcdferaed";
    // getline(cin, s1);
    // getline(cin, s2);
    cout << printlcs(s1, s2) << endl;
}
