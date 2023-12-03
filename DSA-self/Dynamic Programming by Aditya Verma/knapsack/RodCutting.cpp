/*
Rod Cutting
Given a rod of length n inches and an array of prices that contains prices of all pieces of size smaller than n. Determine the maximum value obtainable by cutting up the rod and selling the pieces.

Input:
First line consists of T test cases. First line of every test case consists of n, denoting the size of array. Second line of every test case consists of price of ith length piece.

Output:
For each testcase, in a new line, print a single line output consists of maximum price obtained.

Constraints:
1 <= T <= 100
1 <= n <= 100
1 <= Ai <= 100

Example:
Input:
1
8
1 5 8 9 10 17 17 20
Output:
22
*/
#include <iostream>
using namespace std;
int t[101][101];
int rodCutting(int length[], int price[], int n)
{
    // n is the size of rod
    // n is the size of length array - i.e. type of cuttings possible - might be different 
        // --> in such case length array -> weight array and price array -> val array with different lengths
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            if (i == 0 || j == 0)
                t[i][j] = 0;
        }

    for (int i = 1; i < n + 1; i++)
    {
        for (int j = 1; j < n + 1; j++)
        {

            if (length[i - 1] <= j)
            {
                t[i][j] = max(price[i - 1] + t[i][j - length[i - 1]], t[i - 1][j]);
            }
            else if (length[i - 1] > j)
            {
                t[i][j] = t[i - 1][j];
            }
        }
    }

    return t[n][n];
}
int main()
{
    // code
    int z;
    cin >> z;
    int length[100];
    int price[100];

    for (int i = 0; i < 100; i++)
        length[i] = i + 1;

    while (z--)
    {

        int n;
        cin >> n;

        for (int i = 0; i < n; i++)
            cin >> price[i];

        cout << rodCutting(length, price, n) << endl;
    }
    return 0;
}