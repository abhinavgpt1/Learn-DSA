class Solution {
    int xc[4] = {1, -1, 0, 0};
    int yc[4] = {0, 0, 1, -1};
    bool isWithinBoundary(int _x, int _y, int n, int m){
        if(_x < 0 || _x >= n || _y < 0 || _y >= m)
        return false;
        return true;
    }
    void dfs(vector<vector<int>> &image, int sr, int sc, int n, int m, int newColor){
        int orgColor = image[sr][sc];
        image[sr][sc] = newColor;
        for(int i=0; i<4; i++){
            int _x = sr + xc[i];
            int _y = sc + yc[i];
            if(isWithinBoundary(_x, _y, n, m) && image[_x][_y] == orgColor)
                dfs(image, _x, _y, n, m, newColor);
        }
    }
public:
    vector<vector<int>> floodFill(vector<vector<int>>&image, int sr, int sc, int newColor) {
        if(image[sr][sc] == newColor)
            return image;
        int n = image.size(), m = image[0].size(); 
        dfs(image, sr, sc, n, m, newColor);
        return image;
    }
};
/*
no use of visited
no passing of imageColor in dfs call
*/

//prev soln.
class Solution {
public:
    void dfs(vector<vector<int>>& image, vector<vector<bool>> &visited, int sr, int sc, int n, int m, int theColor, int newColor) {
        if(sr < 0 || sr >= n || sc < 0 || sc >= m || visited[sr][sc] == true || image[sr][sc] != theColor)
            return;
        visited[sr][sc] = true;
        image[sr][sc] = newColor;
        dfs(image, visited, sr + 1, sc, n, m, theColor, newColor);
        dfs(image, visited, sr - 1, sc, n, m, theColor, newColor);
        dfs(image, visited, sr, sc + 1, n, m, theColor, newColor);
        dfs(image, visited, sr, sc - 1, n, m, theColor, newColor);
    }
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int newColor) {
        // Code here 
        int n = image.size();
        int m = image[0].size();
        vector<vector<bool>> visited(n, vector<bool>(m, false));
        dfs(image, visited, sr, sc, n, m, image[sr][sc], newColor);
        return image;
    }
};