class Solution {
  public:
    // Function to find the number of islands.
    void traverseIsland(vector<vector<char>>& grid, int x, int y, int n, int m, vector<vector<bool>> &visited) {
        if(x < 0 || x >= n || y < 0 || y >= m  || grid[x][y] == '0' || visited[x][y])
            return;
        visited[x][y] = true;
        traverseIsland(grid, x + 1, y, n, m, visited);
        traverseIsland(grid, x, y + 1, n, m, visited);
        traverseIsland(grid, x - 1, y, n, m, visited);
        traverseIsland(grid, x, y - 1, n, m, visited);
        traverseIsland(grid, x + 1, y + 1, n, m, visited);
        traverseIsland(grid, x - 1, y + 1, n, m, visited);
        traverseIsland(grid, x - 1, y - 1, n, m, visited);
        traverseIsland(grid, x + 1, y - 1, n, m, visited);
    }
    int numIslands(vector<vector<char>>& grid) {
        int count = 0;
        int n = grid.size(), m = grid[0].size(); 
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(!visited[i][j] && grid[i][j] == '1')
                {
                    traverseIsland(grid, i, j, n, m, visited);
                    count++;
                }
            }
        }
        return count;
    }
};