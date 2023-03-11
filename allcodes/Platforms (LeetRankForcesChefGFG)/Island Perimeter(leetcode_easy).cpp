/*
463. Island Perimeter

Add to List

Share
You are given row x col grid representing a map where grid[i][j] = 1 represents land and grid[i][j] = 0 represents water.

Grid cells are connected horizontally/vertically (not diagonally). The grid is completely surrounded by water, and there is exactly one island (i.e., one or more connected land cells).

The island doesn't have "lakes", meaning the water inside isn't connected to the water around the island. One cell is a square with side length 1. The grid is rectangular, width and height don't exceed 100. Determine the perimeter of the island.



Example 1:


Input: grid = [[0,1,0,0],[1,1,1,0],[0,1,0,0],[1,1,0,0]]
Output: 16
Explanation: The perimeter is the 16 yellow stripes in the image above.
Example 2:

Input: grid = [[1]]
Output: 4
Example 3:

Input: grid = [[1,0]]
Output: 4


Constraints:

row == grid.length
col == grid[i].length
1 <= row, col <= 100
grid[i][j] is 0 or 1.
There is exactly one island in grid.
*/
// 100%
int islandPerimeter(vector<vector<int>> &grid)
{

    int res = 0;
    int r = grid.size();
    int c = grid[0].size();

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            if (grid[i][j] == 1)
            {
                res += (i == 0 || grid[i - 1][j] == 0 ? 1 : 0);
                res += (i == r - 1 || grid[i + 1][j] == 0 ? 1 : 0);
                res += (j == 0 || grid[i][j - 1] == 0 ? 1 : 0);
                res += (j == c - 1 || grid[i][j + 1] == 0 ? 1 : 0);
            }
        }
    }

    return res;
}
// my soln.
class Solution
{
public:
    int getLand(vector<vector<int>> &grid, int i, int j, int m, int n)
    {
        if (i < 0 || i == m || j < 0 || j == n || grid[i][j] == 0)
            return 1;
        return 0; // land
    }
    int solve(vector<vector<int>> &grid, int i, int j, int m, int n)
    {

        int ans =
            getLand(grid, i + 1, j, m, n) +
            getLand(grid, i - 1, j, m, n) +
            getLand(grid, i, j + 1, m, n) +
            getLand(grid, i, j - 1, m, n);
        return ans;
    }
    int islandPerimeter(vector<vector<int>> &grid)
    {
        int m = grid.size(), n = grid[0].size(), ans = 0;
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    ans += solve(grid, i, j, m, n);
                }
            }
        }
        return ans;
    }
};
// wrong approach for linear array - arr[0][0] will be marked corner but it behaves as edge
// corners
// 		dp[0][0] = dp[m - 1][0] = dp[0][n - 1] = dp[m - 1][n - 1] = 2;
// 		// edges
// 		for (int j = 1; j < n - 1; j++)
// 			dp[m - 1][j] = dp[0][j] = 3;
// 		for (int i = 1; i < m - 1; i++)
// 			dp[i][0] = dp[i][n - 1] = 3;
// 			// inner land
// 		for (int i = 1; i < m - 1; i++)
// 		{
// 			for (int j = 1; j < n - 1; j++)
// 				dp[i][j] = 4;
// 		}

// 		for (int i = 0; i < m; i++)
// 		{
// 			for (int j = 0; j < n; j++)
// 			{
// 				if (grid[i][j] == 1)
// 				{
// 					int dir = dp[i][j];
// 					if (dir == 2)
// 					{
// 						if(i == 0 && j == 0)
// 							dp[i][j] = 4 - ((i<m-1 ? grid[i + 1][j] : 0) + (j<n-1 ? grid[i][j + 1] : 0));
// 						if(i == 0 && j == n-1)
// 							dp[i][j] = 4 - ((i<m-1 ? grid[i + 1][j] : 0) + (j>0 ? grid[i][j - 1] : 0));
// 						if(i == m-1 && j == 0)
// 							dp[i][j] = 4 - ((i>0 ? grid[i - 1][j] : 0) + (j<n-1 ? grid[i][j + 1] : 0));
// 						if(i == m-1 && j == n-1)
// 							dp[i][j] = 4 - ((i>0 ? grid[i - 1][j] : 0) + (j>0 ? grid[i][j - 1] : 0));
// 					}
// 					else if (dir == 3)
// 					{
// 						if(i == 0)
// 							dp[i][j] = 4 - (grid[i + 1][j] + grid[i][j + 1] + grid[i][j - 1]);
// 						else if(i == m-1)
// 							dp[i][j] = 4 - (grid[i - 1][j] + grid[i][j + 1] + grid[i][j - 1]);
// 						else if(j == 0)
// 							dp[i][j] = 4 - (grid[i + 1][j] + grid[i - 1][j] + grid[i][j + 1]);
// 						else if(j == n-1)//else
// 							dp[i][j] = 4 - (grid[i + 1][j] + grid[i - 1][j] + grid[i][j - 1]);
// 					}
// 					else
// 					{
// 						dp[i][j] = 4 - (grid[i + 1][j] + grid[i - 1][j] + grid[i][j + 1] + grid[i][j - 1]);
// 					}
// 				}
// 				else
// 					dp[i][j] = 0;
// 			}
// 		}

// 		int sum = 0;
// 		for (int i = 0; i < m; i++)
// 		{
// 			for (int j = 0; j < n; j++)
// 			{
// 				sum += dp[i][j];
// 			}
// 		}
// 		return sum;
