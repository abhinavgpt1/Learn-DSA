/*
1905. Count Sub Islands
Medium
You are given two m x n binary matrices grid1 and grid2 containing only 0's (representing water) and 1's (representing land). An island is a group of 1's connected 4-directionally (horizontal or vertical). Any cells outside of the grid are considered water cells.

An island in grid2 is considered a sub-island if there is an island in grid1 that contains all the cells that make up this island in grid2.

Return the number of islands in grid2 that are considered sub-islands.

 

Example 1:


Input: grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]], grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
Output: 3
Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
The 1s colored red in grid2 are those considered to be part of a sub-island. There are three sub-islands.
Example 2:


Input: grid1 = [[1,0,1,0,1],[1,1,1,1,1],[0,0,0,0,0],[1,1,1,1,1],[1,0,1,0,1]], grid2 = [[0,0,0,0,0],[1,1,1,1,1],[0,1,0,1,0],[0,1,0,1,0],[1,0,0,0,1]]
Output: 2 
Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
The 1s colored red in grid2 are those considered to be part of a sub-island. There are two sub-islands.
 

Constraints:

m == grid1.length == grid2.length
n == grid1[i].length == grid2[i].length
1 <= m, n <= 500
grid1[i][j] and grid2[i][j] are either 0 or 1.
*/
// piyush's soln.
class Solution {
public:
    void dfs(vector<vector<int>>& grid1, vector<vector<int>>& grid2,int i,int j,bool& ans){
        if(grid1[i][j]==0)
            ans=false;
        grid2[i][j]=0;
        if(i>0 && grid2[i-1][j]==1){
            dfs(grid1,grid2,i-1,j,ans);
        }
        if(j>0 && grid2[i][j-1]==1){
            dfs(grid1,grid2,i,j-1,ans);
        }
        if(i<grid1.size()-1 && grid2[i+1][j]==1){
            dfs(grid1,grid2,i+1,j,ans);
        }
        if(j<grid1[0].size()-1 && grid2[i][j+1]==1){
            dfs(grid1,grid2,i,j+1,ans);
        }
    }
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int n=grid1.size();
        int m=grid1[0].size();
        int ans=0;
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                bool sub=true;
                if(grid2[i][j]==1){
                    dfs(grid1,grid2,i,j,sub);
                    if(sub)
                        ans++;
                }
            }
        }
        return ans;
    }
};  
// my soln.
class Solution {
public:
    void exploreIsland(vector<vector<int>>& grid1, vector<vector<int>>& grid2, bool dp[500][500], int row, int col, int m, int n){
        if(row < 0 || col < 0 || row == m || col == n || dp[row][col])
            return;
        dp[row][col] = true;
        if(grid2[row][col] == 1){
            exploreIsland(grid1, grid2, dp, row + 1, col, m, n);
            exploreIsland(grid1, grid2, dp, row - 1, col, m, n);
            exploreIsland(grid1, grid2, dp, row, col + 1, m, n);
            exploreIsland(grid1, grid2, dp, row, col - 1, m, n);
        }
    }
    int countSubIslands(vector<vector<int>>& grid1, vector<vector<int>>& grid2) {
        int m = grid1.size(), n = grid1[0].size();
        bool dp[500][500];
        memset(dp, 0, sizeof(dp));
        //marking islands not eligible
        for(int i=0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(dp[i][j] == 0 && grid2[i][j] == 1 && grid1[i][j] == 0)
                {
                    exploreIsland(grid1, grid2, dp, i, j, m, n);
                }
                else if(grid2[i][j] == 0)
                    dp[i][j] = true;
            }
        }
        
        int count = 0;
        for(int i=0; i<m; i++){
            for(int j = 0; j<n; j++){
                if(!dp[i][j])
                {
                    exploreIsland(grid1, grid2, dp, i, j, m, n);
                    count++;
                }
            }
        }
        return count;   
    }
};