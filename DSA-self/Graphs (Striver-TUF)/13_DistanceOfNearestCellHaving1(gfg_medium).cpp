/**
 * Distance of nearest cell having 1
 * ---------------------------------
 * Given a binary grid of n*m. Find the distance of the nearest 1 in the grid for each cell.
 * The distance is calculated as |i1  - i2| + |j1 - j2|, 
 * where i1, j1 are the row number and column number of the current cell, 
 * and i2, j2 are the row number and column number of the nearest cell having value 1. 
 * There should be atleast one 1 in the grid.
 * 
 */

 //link: https://www.geeksforgeeks.org/problems/distance-of-nearest-cell-having-1-1587115620/1
 //editorial: https://www.geeksforgeeks.org/distance-nearest-cell-1-binary-matrix/

 // Solution 1: using BFS (inwards i.e. queueing all 1s first and then traversing outwards): O(n*m), O(n*m)
 // just like 10_rottenOranges(gfg_medium).cpp problem
 class Solution 
{
    bool isWithinBoundary(int xdash, int ydash, int n, int m){
        if(xdash < 0 || xdash >= n || ydash < 0 || ydash >= m)
            return false;
        return true;
    }
    public:
    //Function to find distance of nearest 1 in the grid for each cell.
	vector<vector<int>>nearest(vector<vector<int>>grid)
	{
	    int n = grid.size(), m = grid[0].size();
	    vector<vector<int>> ans(n, vector<int>(m, -1));
	    queue<pair<int, int>> pending;
	    for(int i=0; i<n; i++){
	        for(int j=0; j<m; j++){
	            if(grid[i][j] == 1)
	            {
	                ans[i][j] = 0;
	                pending.push({i,j});
	            }
	        }
	    }
	    int xd[] = {1, -1, 0, 0};
	    int yd[] = {0, 0, 1, -1};
	    while(!pending.empty()){
	        int x = pending.front().first;
	        int y = pending.front().second;
	        pending.pop();
	        
	        for(int i=0; i<4; i++){
                int xn = xd[i] + x;
	            int yn = yd[i] + y;
	            if(isWithinBoundary(xn, yn, n, m) && ans[xn][yn] == -1) //checking withing boundary and not visited(at this time it doesn't matter if [xn][yn] is 1 or anything)
                {
                    ans[xn][yn] = ans[x][y] + 1;
                    pending.push({xn, yn});    
                }
	        }
	    }
	    return ans;
	}
};

// not optimal
// Solution 2: using BFS (outwards i.e. doing bfs by traversing all cells to calculate their ans respectively): O(n^2*m^2+2E), O(n*m)
class Solution{
int findMyAns(vector<vector<int>> &grid, int x, int y, vector<vector<int>> &ans){
    if(grid[x][y] == 1){
        ans = 0;
        return;
    }
    vector<pair<int, int>> pending;
    pending.push({x,y});
    pending.push({-1,-1});
    int level = 0;
    while(!pending.empty()){
        int i = pending.front().first;
        int j = pending.front().second;
        pending.pop();
        if(i == -1)
        {
            level++;
            if(!pending.empty())
            pending.push({-1,-1});
        }
        
        // further steps:
        // - traverse of adj list
        // - check if ans[xn][yn] exist
        // - if yes, return ans + 1;
        
    }
    return level-1;
}
public:
// Function to find distance of nearest 1 in the grid for each cell.
vector<vector<int>> nearest(vector<vector<int>>& grid) {
    int n = grid.size(), m = grid[0].size();
    vector<vector<int>> ans(n, vector<int>(m,-1));
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            if(ans[i][j] == -1)
                ans[i][j] = findMyAns(grid, i, j, ans);
        }
    }
    return ans;
    //since ans is not stored for coordinates traversed, hence dp/ans won't be of much help
    //complexity - O(n*m) * O(n*m) = O(n^2*m^2)
}
};