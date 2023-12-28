/*
 * You are a hiker preparing for an upcoming hike. 
 * You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of cell (row, col). You are situated in the top-left cell, (0, 0), 
 * and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). 
 * You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.
 * 
 * A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.
*/

// Dijkstra like problem with different definition to distance[node]

class Solution { //ElogV = 4NMlog(NM)
  public:
    int MinimumEffort(vector<vector<int>>& heights) {
        int x_src = 0, y_src = 0;
        // Distance to a node is not constant, but calculated as difference of heights from parent and itself
        // Our approach remains same i.e. to keep the distance minimum (though the defintion of distance is changed now)
        // At last, among all 3 cells surronding dest cell, choose the minimum distance which is our answer
        int n = heights.size(), m = heights[0].size();
        vector<vector<int>> effort(n, vector<int>(m, INT_MAX));
        int xd[4] = {1,-1,0,0};
        int yd[4] = {0,0,1,-1};
        set<pair<int, pair<int, int>>> pending;
        effort[x_src][y_src] = 0;
        pending.insert({effort[x_src][y_src], {x_src, y_src}});
        while(!pending.empty()){
            auto it = pending.begin();
            pending.erase(it);
            
            int effortXY = it->first;
            int x = it->second.first;
            int y = it->second.second;
            
            if(x == n - 1 && y == m-1)
                return effortXY;
            
            for(int i=0; i<4; i++){
                int _x = x + xd[i];
                int _y = y + yd[i];
                if(_x>=0 && _x<n && _y>=0 && _y<m){
                    //visited can be used here to simply skip cells visited once (after popping from set)
                    int effort_X_Y = max(abs(heights[_x][_y] - heights[x][y]), effortXY); // taking maximum absolute difference in heights in the entire path to reach {_x, _y}
                    if(effort[_x][_y] > effort_X_Y){ // minimizing the effort to {_x, _y}
                        if(effort[_x][_y] != INT_MAX)
                            pending.erase({effort[_x][_y], {_x, _y}});
                            
                        effort[_x][_y] = effort_X_Y;
                        pending.insert({effort[_x][_y], {_x, _y}});
                    }
                }
            }
        }
        return -1;
    }
};