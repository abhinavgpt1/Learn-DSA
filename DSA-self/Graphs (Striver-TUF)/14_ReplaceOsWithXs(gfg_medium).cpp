/**
 * Replace O's with X's
 * --------------------
 * Given a matrix mat where every element is either 'O' or 'X'. 
 * Replace all 'O' or a group of 'O' with 'X' that are surrounded by 'X'.
 * A 'O' (or a set of 'O') is considered to be surrounded by 'X' if there are 'X' at locations
 * just below, just above, just left and just right of it.
 * 
 */

 // link: https://www.geeksforgeeks.org/problems/replace-os-with-xs0052/1
 // editorial: https://www.geeksforgeeks.org/given-matrix-o-x-replace-o-x-surrounded-x/

 // similar question link: https://www.geeksforgeeks.org/problems/number-of-enclaves/1

/*
2 approaches
1. DFS on boundary 'O' and mark the leftover(unvisited) 'O'
2. Traverse all components of 'O' and based on a flag (isSurr == (isOnBoundary == true:false)) convert them to 'X'. 
    This will involve storing the component as edge list
*/

// Solution: Approach 1 - optimal & intuitive - O(m*n), O(m*n)
class Solution{
    int xd[4] = {1, -1, 0, 0};
    int yd[4] = {0, 0, 1, -1};
    void dfs(vector<vector<char>> &mat, vector<vector<bool>> &visited, int n, int m, int x, int y){
        visited[x][y] = true;
        for(int i=0; i<4; i++){
            int xx = x + xd[i];
            int yy = y + yd[i];
            if(xx >= 0 && xx < n && yy >= 0 && yy < m && !visited[xx][yy] && mat[xx][yy] == 'O')
                dfs(mat, visited, n, m, xx, yy);
        }
    }
public:
    vector<vector<char>> fill(vector<vector<char>> mat)
    {
        int n = mat.size(), m = mat[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        vector<vector<char>> ans = mat;
        for(int i=0; i<n; i++){
            if(mat[i][0] == 'O' && !visited[i][0])
                dfs(mat, visited, n, m, i, 0);
            if(mat[i][m-1] == 'O' && !visited[i][m-1])
                dfs(mat, visited, n, m, i, m-1);
        }
        for(int j=1; j<m-1; j++){
            if(mat[0][j] == 'O' && !visited[0][j])
                dfs(mat, visited, n, m, 0, j);
            if(mat[n-1][j] == 'O' && !visited[n-1][j])
                dfs(mat, visited, n, m, n-1, j);
        }
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(!visited[i][j] && mat[i][j] == 'O')
                    ans[i][j] = 'X';
            }
        }
        return ans;
    }
};

// Solution: Approach 2 - less performant - O(m*n) + edges iteration = O(m*n), O(m*n)
class Solution{
    bool isSurr = true;
    vector<pair<int, int>> traverseComp(int x, int y, int n, int m, vector<vector<bool>> &visited, vector<vector<char>> &mat){
        
        if(x == 0 || x == n-1 || y == 0 || y == m-1){
            if(mat[x][y] == 'O')
                isSurr = false;
            return {};
        }
        if(visited[x][y] || mat[x][y] == 'X') //can be combined with above logic since if condition will be redundant
            return {};

        vector<pair<int, int>> ans;
        visited[x][y] = true;
        ans.push_back({x,y});
        
        auto a1 = traverseComp(x+1, y, n, m, visited, mat);
        auto a2 = traverseComp(x-1, y, n, m, visited, mat);
        auto a3 = traverseComp(x, y+1, n, m, visited, mat);
        auto a4 = traverseComp(x, y-1, n, m, visited, mat);
        if(isSurr){
            for(auto xy: a1)
                ans.push_back(xy);
            
            for(auto xy: a2)
                ans.push_back(xy);
            
            for(auto xy: a3)
                ans.push_back(xy);
            
            for(auto xy: a4)
                ans.push_back(xy);
            
        }
        
        return ans;
    }
public:
    vector<vector<char>> fill(vector<vector<char>> mat)
    {
        int n = mat.size(), m = mat[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(!visited[i][j] && mat[i][j] == 'O'){
                    vector<pair<int, int>> component = traverseComp(i, j, n, m, visited, mat);
                    if(isSurr){
                        for(auto p: component){
                            int r = p.first; int c = p.second;
                            mat[r][c] = 'X';
                            visited[r][c] = true;
                        }
                    }
                    isSurr = true; //when 'O' is at boundary, this needs to reset for next component scan
                }
            }
        }
        return mat;
    }
};