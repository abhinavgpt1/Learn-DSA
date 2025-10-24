// BFS approach
class Solution {
    const int xchange[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    const int ychange[8] = {0, 0, 1, -1, 1, -1, 1, -1};
    
    bool checkIsNodeTraversable(vector<vector<char>> &grid, int n, int m, int x, int y, vector<vector<bool>> &visited){
        if(x >= n || x < 0 || y >= m || y < 0 || grid[x][y] == '0' || visited[x][y])
            return false;
        return true;
    }
    
    void bfs(vector<vector<char>> &grid, int n, int m, int x, int y, vector<vector<bool>> &visited){
        queue<pair<int, int>> pending;
        pending.push({x, y});
        visited[x][y] = true;
        while(!pending.empty()){
            pair<int, int> front = pending.front();
            pending.pop();
            for(int i=0; i<8; i++){
                int xnew = front.first + xchange[i];
                int ynew = front.second + ychange[i];
                if(checkIsNodeTraversable(grid, n, m, xnew, ynew, visited)){
                    pending.push({xnew, ynew});
                    visited[xnew][ynew] = true;
                }
            }
            
        }
    }
  public:
    // Function to find the number of islands.
    int numIslands(vector<vector<char>>& grid) {
        //BFS
        int n = grid.size(), m = grid[0].size(), cnt = 0;
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(grid[i][j] == '1' && !visited[i][j])
                {
                    cnt++;
                    bfs(grid, n, m, i, j, visited);
                }
            }
        }
        return cnt;
    }
};

// DFS approach
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