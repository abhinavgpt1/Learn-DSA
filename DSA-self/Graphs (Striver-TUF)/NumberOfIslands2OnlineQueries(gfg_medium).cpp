/**
 * Number Of Islands 2 - Online queries DSU
 * -----------------
 * You are given a n,m which means the row and column of the 2D matrix 
 * and an array of size k denoting the number of operations. 
 * Matrix elements is 0 if there is water or 1 if there is land. 
 * Originally, the 2D matrix is all 0 which means there is no land in the matrix. 
 * The array has k operator(s) and each operator has two integer A[i][0], A[i][1] means that you can change the cell matrix[A[i][0]][A[i][1]] from sea to island. 
 * Return how many island are there in the matrix after each operation.
 * You need to return an array of size k.
 * Note : An island means group of 1s such that they share a common side.
 * 
 */

// Solution 1: Efficient due to cell tracking as int and finding component cnt by int "cnt" variable, reducing complexity from O(KMN)=O((NM)^2) to O(NM)
class DisjointSet{
    vector<int> size;
    vector<int> parent; // tracks which cell connects which
    
    public:
    DisjointSet(int n){ 
        size.resize(n, 1);
        parent.resize(n);
        for(int i=0; i<n; i++)
            parent[i] = i;
    }
    int findParent(int u){
        if(parent[u] == u)
            return u;
        return parent[u] = findParent(parent[u]); //path compression
    }
    void unionBySize(int u, int v){
        int pu = findParent(u);
        int pv = findParent(v);
        if(pu == pv)
            return;
        if(size[pu] < size[pv]){
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};
class Solution {
  public:
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators) {
        // Optimazations:
        // 2D grid linearized -> thus no tracking by pair<int, int>
        // Checking components by a simple int and not traversing whole grid again. 
        // So, complexity goes from O(KMN) -> O(K), Sn = O(n*m)
        // K can be max. N*M -> so complexity = O(NM) for time and space
        
        int xd[4] = {1, -1, 0, 0};
        int yd[4] = {0, 0, 1, -1};
        DisjointSet ds(n*m);
        vector<vector<bool>> isLand(n, vector<bool>(m, false)); //needed to connect lands only
        vector<int> ans;
        int cnt = 0;
        // O(K*(c+...+4c+...+c)) = O(K)
        for(vector<int> cell: operators){
            int row = cell[0];
            int col = cell[1];
            if(isLand[row][col]){ // no need to process a switched land from sea
                ans.push_back(cnt);
                continue;
            }
            isLand[row][col] = true;
            cnt++; //assuming this cell will be a sole component
            
            // Component tracking starts here
            for(int i=0; i<4; i++){
                int adjX = row + xd[i];
                int adjY = col + yd[i];
                if(adjX < 0 || adjX >= n || adjY < 0 || adjY >= m || !isLand[adjX][adjY])
                    continue;

                int nodeNum = row*m + col;
                int adjNodeNum = adjX*m + adjY;
                int pNode = ds.findParent(nodeNum);
                int pAdjNode = ds.findParent(adjNodeNum);
                if(pNode == pAdjNode)
                    continue; // already connected
                cnt--; // two sets are combined (count of both is included already in cnt variable)
                ds.unionBySize(pNode, pAdjNode);
            }
            ans.push_back(cnt);
        }
        return ans;
    }
};
// Solution 2: less efficient and clumsy due to cell tracking as pair<int, int>
class DisjointSet{
    int sets = 0;
    vector<vector<int>> size;
    vector<vector<pair<int, int>>> parent; // tracks which cell it connects to, thus maintaining an island
    public:
    DisjointSet(int n, int m){
        size.resize(n, vector<int>(m, 1));
        parent.resize(n, vector<pair<int, int>>(m));
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                parent[i][j] = {i, j};
    }
    pair<int, int> findParent(pair<int, int> pp){
        if(parent[pp.first][pp.second] == make_pair(pp.first, pp.second))
            return pp;
        return parent[pp.first][pp.second] = findParent(parent[pp.first][pp.second]); //path compression
    }
    void unionBySize(pair<int, int> pp1, pair<int, int> pp2){
        pair<int, int> ppp1 = findParent(pp1);
        pair<int, int> ppp2 = findParent(pp2);
        if(ppp1 == ppp2) // cell lands are connected already
            return;
        if(size[ppp1.first][ppp1.second] < size[ppp2.first][ppp2.second]){
            parent[ppp1.first][ppp1.second] = ppp2;
            size[ppp2.first][ppp2.second] += size[ppp1.first][ppp1.second];
        } else {
            parent[ppp2.first][ppp2.second] = ppp1;
            size[ppp1.first][ppp1.second] += size[ppp2.first][ppp2.second];
        }
    }
};
class Solution {
    int findConnectedComponents(vector<vector<bool>> &isLand, int n, int m, DisjointSet &ds){
        int cnt = 0;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                if(ds.findParent({i, j}) == make_pair(i, j) && isLand[i][j])
                    cnt++;
            }
        }
        return cnt;
    }
  public:
    vector<int> numOfIslands(int n, int m, vector<vector<int>> &operators) {
        // First soln. that comes is that it can be solved with DFS done K times -> O(K*N*M)
        // No harm if cell in operators is repeated
        int xd[4] = {1, -1, 0, 0};
        int yd[4] = {0, 0, 1, -1};
        DisjointSet ds(n, m);
        vector<vector<bool>> isLand(n, vector<bool>(m, false));
        vector<int> ans;
        for(vector<int> cell: operators){
            // need to maintain a matrix and mark a cell as land
            isLand[cell[0]][cell[1]] = true;
            for(int i=0; i<4; i++){
                int adjX = cell[0] + xd[i];
                int adjY = cell[1] + yd[i];
                if(adjX < 0 || adjX >= n || adjY < 0 || adjY >= m || !isLand[adjX][adjY])
                    continue;

                pair<int, int> pCell = ds.findParent({cell[0], cell[1]});
                pair<int, int> pAdjCell = ds.findParent({adjX, adjY});
                if(pCell == pAdjCell)
                    continue; // already connected
                ds.unionBySize(pCell, pAdjCell);
            }
            ans.push_back(findConnectedComponents(isLand, n, m, ds));
        }
        return ans;
    }
};