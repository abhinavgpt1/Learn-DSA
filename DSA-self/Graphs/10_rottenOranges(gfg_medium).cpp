#include<bits/stdc++.h>
class Solution 
{
    bool isWithinBoundary(int _x, int _y, int n, int m){
        if(_x < 0 || _x >=n | _y <0 || _y >=m)
        return false;
        return true;
    }
    public:
    //Function to find minimum time required to rot all oranges.
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size(), count = 0, cntFresh = 0;
        int xc[] = {1, -1, 0, 0};
        int yc[] = {0, 0, 1, -1};
        
        queue<pair<int, int>> pending;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(grid[i][j] == 2)
                    pending.push({i, j});
                if(grid[i][j] == 1)
                    cntFresh++;
            }
        }
        pending.push({-1, -1});
        int orangesRotted = 0;
        while(!pending.empty()){
            int x = pending.front().first;
            int y = pending.front().second;
            pending.pop();

            if(x == -1){
                count++;
                if(!pending.empty())
                    pending.push({-1, -1});
                
                continue;
            }
            
            for(int i=0; i<4; i++){
                int _x = xc[i] + x;
                int _y = yc[i] + y;
                if(isWithinBoundary(_x, _y, n, m) && grid[_x][_y] == 1)
                {
                    grid[_x][_y] = 2;
                    pending.push({_x, _y});
                    orangesRotted++;    
                }
            }
        }
        if(orangesRotted != cntFresh)
            return -1;
        return count-1;
    }
};
/**
 * @brief 
 * Above is Optimal solution:
 * -> changing grid values
 * -> not using visited
 * -> counting fresh oranges by counter
 * -> counting time via {-1, -1}
 */

//prev. best -> in case no inplace updation. Can optimise on {{},} to {-1, -1} usage
class Solution 
{
    public:
    //Function to find minimum time required to rot all oranges.
    int orangesRotting(vector<vector<int>>& grid) {
        int n = grid.size(), m = grid[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        queue<pair<pair<int, int>, int>> pending;
        
        int cntFresh = 0, maxTime = 0;
        int xdiff[] = {1, -1, 0, 0};
        int ydiff[] = {0, 0, 1, -1};
        
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(grid[i][j] == 2){
                    visited[i][j] = true;
                    pending.push({{i, j}, 0});
                }
                if(grid[i][j] == 1)
                    cntFresh++;
            }
        }
        
        int orangesRotted = 0;
        while(!pending.empty()){
            int r = pending.front().first.first;
            int c = pending.front().first.second;
            int t = pending.front().second;
            pending.pop();
            
            maxTime = max(maxTime, t);
            
            for(int i=0; i<4; i++){
                int xnew = xdiff[i] + r;
                int ynew = ydiff[i] + c;
                if(xnew < 0 || xnew >= n || ynew < 0 || ynew >= m || visited[xnew][ynew] || grid[xnew][ynew] != 1)
                    continue;
                pending.push({{xnew, ynew}, t+1});
                visited[xnew][ynew] = true;
                orangesRotted++;
            }
        }
        
        if(orangesRotted != cntFresh)
            return -1;
        return maxTime;
    }
};