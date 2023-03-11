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
        // if (t[i][j] == t[i - 1][j - 1] + 1)
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