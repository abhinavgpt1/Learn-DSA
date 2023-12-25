/*
Number of Distinct Islands
MediumAccuracy: 62.29%Submissions: 56K+Points: 4
Given a boolean 2D matrix grid of size n * m. You have to find the number of distinct islands where a group of connected 1s (horizontally or vertically) forms an island. Two islands are considered to be distinct if and only if one island is not equal to another (not rotated or reflected).

Example 1:

Input:
grid[][] = {{1, 1, 0, 0, 0},
            {1, 1, 0, 0, 0},
            {0, 0, 0, 1, 1},
            {0, 0, 0, 1, 1}}
Output:
1
Explanation:
grid[][] = {{1, 1, 0, 0, 0}, 
            {1, 1, 0, 0, 0}, 
            {0, 0, 0, 1, 1}, 
            {0, 0, 0, 1, 1}}
Same colored islands are equal.
We have 2 equal islands, so we 
have only 1 distinct island.

Example 2:

Input:
grid[][] = {{1, 1, 0, 1, 1},
            {1, 0, 0, 0, 0},
            {0, 0, 0, 0, 1},
            {1, 1, 0, 1, 1}}
Output:
3
Explanation:
grid[][] = {{1, 1, 0, 1, 1}, 
            {1, 0, 0, 0, 0}, 
            {0, 0, 0, 0, 1}, 
            {1, 1, 0, 1, 1}}
Same colored islands are equal.
We have 4 islands, but 2 of them
are equal, So we have 3 distinct islands.

Your Task:

You don't need to read or print anything. Your task is to complete the function countDistinctIslands() which takes the grid as an input parameter and returns the total number of distinct islands.

Expected Time Complexity: O(n * m)
Expected Space Complexity: O(n * m)

Constraints:
1 ≤ n, m ≤ 500
grid[i][j] == 0 or grid[i][j] == 1


*/

// 3 ways
// 1. Store island as vector<pair<int, int>> and distIsland as set of it
// 2. Strore island as string of coordinates 
// 3. Store island w.r.t. the directions you take. Taking backtrack step is equally imp.

class Solution {
    vector<pair<int, int>> island;
    set<vector<pair<int, int>>> distIslands;
    void dfsAndInsertToSet(vector<vector<int>> &grid, vector<vector<bool>> &visited, int n, int m, int x, int y, int xref, int yref){
        if(x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || grid[x][y] == 0)
            return;
        visited[x][y] = true;
        island.push_back({x-xref, y-yref}); //way1
        // (string) island += to_string(x-xref) + to_string(y-yref); //way2

        dfsAndInsertToSet(grid, visited, n, m, x+1, y, xref, yref);
        dfsAndInsertToSet(grid, visited, n, m, x-1, y, xref, yref);
        dfsAndInsertToSet(grid, visited, n, m, x, y+1, xref, yref);
        dfsAndInsertToSet(grid, visited, n, m, x, y-1, xref, yref);
    }
  public:
    int countDistinctIslands(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(grid[i][j] == 1 && !visited[i][j]){
                    island.clear();
                    dfsAndInsertToSet(grid, visited, n, m, i, j, i, j);
                    distIslands.insert(island);
                }
            }
        }
        return distIslands.size();
    }
};

// User function Template for C++

// https://www.pepcoding.com/resources/data-structures-and-algorithms-in-java-levelup/graphs/number-of-distinct-island-official/ojquestion
class Solution {
    set<string> islandCodes;
    string dfs(int x, int y, int n, int m, vector<vector<bool>> &visited, vector<vector<int>> &grid, string code){
        if(x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || grid[x][y] == 0)
            return "";
        visited[x][y] = true;
        
        code += dfs(x+1, y, n, m, visited, grid, "D");
        code += dfs(x-1, y, n, m, visited, grid, "U");
        code += dfs(x, y+1, n, m, visited, grid, "R");
        code += dfs(x, y-1, n, m, visited, grid, "L");
        code += "B";//backtrack counted
        return code;
    }
  public:
    int countDistinctIslands(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(!visited[i][j] && grid[i][j] == 1)
                    islandCodes.insert(dfs(i, j, n, m, visited, grid, "X"));
            }
        }
        return islandCodes.size();
    }
};