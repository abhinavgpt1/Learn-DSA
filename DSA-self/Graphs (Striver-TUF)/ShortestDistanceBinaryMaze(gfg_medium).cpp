/*
 * Given a n * m matrix grid where each element can either be 0 or 1. 
 * You need to find the shortest distance between a given source cell to a destination cell. 
 * The path can only be created out of a cell if its value is 1. 
 * 
 * If the path is not possible between source cell and destination cell, then return -1.
 * 
 * Note : You can move into an adjacent cell if that adjacent cell is filled with element 1. Two cells are adjacent if they share a side. 
 * In other words, you can move in one of the four directions, Up, Down, Left and Right. 
 * The source and destination cell are based on the zero based indexing. The destination cell should be 1.
*/
// [Eye opener problem] Similar to Shortest Distance in Undirected graph with Unit weight -> Solved by BFS efficiently (No need of Dijkstra)
// https://practice.geeksforgeeks.org/problems/shortest-path-in-undirected-graph-having-unit-distance/1?utm_source=youtube&utm_medium=collab_striver_ytdescription&utm_campaign=shortest-path-in-undirected-graph-having-unit-distance

// Solution 1: Standard BFS - O(V+E)
class Solution {
    // It can be solved by BFS alone since weight = 1. If weight is not constant, then it would require dijkstra (1)using set (2)using visited(2D)
    // No need of dijkstra
  public:
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source,
                     pair<int, int> destination) {
        // no boundation on source being 0
        if(grid[destination.first][destination.second] == 0)
            return -1;
        int n = grid.size();
        int m = grid[0].size();
        int xd[4] = {1,-1,0,0};
        int yd[4] = {0,0,1,-1};
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        queue<pair<pair<int, int>, int>> pending;
        pending.push({source, 0});
        while(!pending.empty()){
            int x = pending.front().first.first;
            int y = pending.front().first.second;
            int distXY = pending.front().second;
            pending.pop();
            
            if(x == destination.first && y == destination.second)
                return distXY;
            
            for(int i=0; i<4; i++){
                int _x=x+xd[i];
                int _y=y+yd[i];
                if(_x>=0 && _x<n && _y>=0 && _y<m && grid[_x][_y] == 1 && !visited[_x][_y]){
                    visited[_x][_y] = true;
                    pending.push({{_x,_y}, distXY + 1});
                }
            }
        }
        return -1;
    }
};

// Solution 2: Dijkstra -> useful when edge weight is not constant
// T(n) = O(NMlog(NM)) 
class Solution {
  public:
    int shortestPath(vector<vector<int>> &grid, pair<int, int> source,
                     pair<int, int> destination) {
        // no boundation on source being 0
        if(grid[destination.first][destination.second] == 0)
            return -1;

        int n = grid.size(), m = grid[0].size();
        int xd[4] = {1, -1, 0, 0};
        int yd[4] = {0, 0, 1, -1};
        vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
        set<pair<int, pair<int, int>>> pending;
        dist[source.first][source.second] = 0;
        pending.insert({0, source});
        
        while(!pending.empty()){
            auto it = pending.begin();
            pending.erase(it);
            int x = it->second.first;
            int y = it->second.second;
            int distNode = it->first;
            
            if(x == destination.first && y == destination.second)
                return distNode;
            for(int i=0; i<4; i++){
                int _x = x + xd[i];
                int _y = y + yd[i];
                if(_x >= 0 && _x < n && _y >= 0 && _y < m && grid[_x][_y] == 1){
                    if(dist[_x][_y] > distNode + 1){
                        if(dist[_x][_y] != INT_MAX){
                            pending.erase({dist[_x][_y], {_x, _y}});
                        }
                        dist[_x][_y] = dist[x][y] + 1;
                        pending.insert({dist[_x][_y], {_x, _y}});
                    }
                }
            }
        }
        return -1;
    }
};

// Solution 3: Using visited array (2D) - T(n) = O((MN)^2)