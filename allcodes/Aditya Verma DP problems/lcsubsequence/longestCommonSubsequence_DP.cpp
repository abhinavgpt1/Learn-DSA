#include <bits/stdc++.h>
using namespace std;
int t[1001][1001];
int helper(string s1, string s2, int n, int m)
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
    return t[n][m];
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

/*
similar problem - lc substring
|
-->soln. - as soon as chars don't match return 0
         - in dp - put t[i][j] = 0 straightaway