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
