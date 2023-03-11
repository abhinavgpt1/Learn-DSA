/*
B. Interesting drink
time limit per test
2 seconds
memory limit per test
256 megabytes
input
standard input
output
standard output

Vasiliy likes to rest after a hard work, so you may often meet him in some bar nearby. As all programmers do, he loves the famous drink "Beecola", which can be bought in n different shops in the city. It's known that the price of one bottle in the shop i is equal to xi coins.

Vasiliy plans to buy his favorite drink for q consecutive days. He knows, that on the i-th day he will be able to spent mi coins. Now, for each of the days he want to know in how many different shops he can buy a bottle of "Beecola".
Input

The first line of the input contains a single integer n (1 ≤ n ≤ 100 000) — the number of shops in the city that sell Vasiliy's favourite drink.

The second line contains n integers xi (1 ≤ xi ≤ 100 000) — prices of the bottles of the drink in the i-th shop.

The third line contains a single integer q (1 ≤ q ≤ 100 000) — the number of days Vasiliy plans to buy the drink.

Then follow q lines each containing one integer mi (1 ≤ mi ≤ 109) — the number of coins Vasiliy can spent on the i-th day.
Output

Print q integers. The i-th of them should be equal to the number of shops where Vasiliy will be able to buy a bottle of the drink on the i-th day.
Example
Input
5
3 10 8 6 11
4
1
10
3
11

Output
0
4
1
5

Note

On the first day, Vasiliy won't be able to buy a drink in any of the shops.

On the second day, Vasiliy can buy a drink in the shops 1, 2, 3 and 4.

On the third day, Vasiliy can buy a drink only in the shop number 1.

Finally, on the last day Vasiliy can buy a drink in any shop.
*/
//editorial
// https://codeforces.com/blog/entry/46510
// Consider c[x] the number of stores in which the price per drink is x. We calculate this array prefix sum. Then the following options:

// 1) If the current amount of money m is larger than the size of the array with the prefix sums than answer is n.

// 2) Otherwise, the answer is c[m].

// Time Complexity: O(n+q).
//my solution
#include <bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    cin >> n;
    vector<int> cost(n);
    for (int i = 0; i < n; i++)
        cin >> cost[i];
    int q;
    cin >> q;
    vector<pair<int, int>> inhand;
    for (int i = 0; i < q; i++)
    {
        int x;
        cin >> x;
        inhand.push_back({x, i});
    }

    sort(cost.begin(), cost.end());
    sort(inhand.begin(), inhand.end());
    vector<int> ans(q, 0);
    int inj = 0, i = 0;
    while (i < n && inj < q)
    {
        if (inhand[inj].first >= cost[i])
            i++;
        else
        {
            ans[inhand[inj].second] = i;
            inj++;
        }
    }
    while (inj < q)
    {
        ans[inhand[inj].second] = i;
        inj++;
    }
    for(auto x: ans)
    cout<<x<<endl;
}
//TLE: not wrong though
int binary_search_index(vector<int> cost, int st, int end, int x)
{
    int mid = (end + st) / 2;
    if (end < st)
        return end + 1;
    if (x < cost[mid])
        return binary_search_index(cost, st, mid - 1, x);
    else
        return binary_search_index(cost, mid + 1, end, x);
}