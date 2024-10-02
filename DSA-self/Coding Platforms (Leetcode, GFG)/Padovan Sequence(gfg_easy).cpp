/**
 * Padovan Sequence
 * ----------------
 * Given a number n, find the nth number in the Padovan Sequence.
 *
 * A Padovan Sequence is a sequence which is represented by the following recurrence relation
 * P(n) = P(n-2) + P(n-3)
 * P(0) = P(1) = P(2) = 1
 *
 * Note: Since the output may be too large, compute the answer modulo 10^9+7
 *
 * Expected Time Complexity: O(n)
 * Expected Auxiliary Space: O(1)
 *
 * Constraints:
 * 1 <= n <= 10^6
 */
// link: https://www.geeksforgeeks.org/problems/padovan-sequence2855/1
// article: https://www.geeksforgeeks.org/padovan-sequence/

// Solution 1: Bottom-up: O(n), O(1)
class Solution
{
public:
    int padovanSequence(int n)
    {
        if (n <= 2)
            return 1;
        int p0, p1, p2, MOD = 1e9 + 7;
        p0 = p1 = p2 = 1;
        for (int i = 3; i <= n; i++)
        {
            int p = (p0 + p1) % MOD;
            p0 = p1;
            p1 = p2;
            p2 = p;
        }
        return p2;
    }
};

// Solution 2: Memoization: O(n), O(n) + stack space(O(n))
#include <iostream>
#include <cstring>
using namespace std;
long long int t[101];
long long int padovan(int n)
{

    if (n == 0 || n == 1 || n == 2)
        return 1;

    if (t[n] != 0)
        return t[n];

    long long int ans = t[n] = (padovan(n - 2) + padovan(n - 3)) % 1000000007;
    return ans;
}
int main()
{
    // code
    memset(t, 0, sizeof(t));
    t[0] = t[1] = t[2] = 1;
    int z;
    cin >> z;
    while (z--)
    {
        int n;
        cin >> n;
        cout << padovan(n) << endl;
    }
    return 0;
}