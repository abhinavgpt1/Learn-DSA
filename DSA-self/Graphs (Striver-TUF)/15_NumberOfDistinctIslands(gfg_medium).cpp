/**
 * Number of Distinct Islands
 * --------------------------
 * Given a boolean 2D matrix grid of size n * m. 
 * You have to find the number of distinct islands where a group of connected 1s (horizontally or vertically) forms an island. 
 * Two islands are considered to be distinct if and only if one island is not equal to another (not rotated or reflected).
 * 
 */

 //link: https://www.geeksforgeeks.org/problems/number-of-distinct-islands/1
 //editorial: https://www.geeksforgeeks.org/find-the-number-of-distinct-islands-in-a-2d-matrix/

// Solution 1: Tracking subgraph by directions - O(n*m*log(n*m)), O(n*m) - log(n*m) for set insertion of max n*m coordinates as graph
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

// Solution 2 (editorial): Tracking subgraph set of coordinates w.r.t. starting point. - O(n*m*log(n*m)), O(n*m) - for set insertion of max n*m coordinates as graph
// Finally storing in a set to get unique islands.
class Solution {
    vector<pair<int, int>> island;
    set<vector<pair<int, int>>> distIslands;
    void dfsAndInsertToSet(vector<vector<int>> &grid, vector<vector<bool>> &visited, int n, int m, int x, int y, int xref, int yref){
        if(x < 0 || x >= n || y < 0 || y >= m || visited[x][y] || grid[x][y] == 0)
            return;
        visited[x][y] = true;
        island.push_back({x-xref, y-yref});
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