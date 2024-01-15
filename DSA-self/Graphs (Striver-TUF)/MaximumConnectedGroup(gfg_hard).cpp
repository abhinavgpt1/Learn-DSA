/**
 * Maximum Connected Group
 * -----------------------
 * You are given an n x n binary grid. A grid is said to be binary if every value in grid is either 1 or 0.
 * You can change at most one cell in grid from 0 to 1.
 * You need to find the largest group of connected  1's.
 * Two cells are said to be connected if both are adjacent to each other and both have same value.
 * 
 */

// Solution 1: cleaner
// User function Template for C++
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
    int getSize(int u){
        return size[u];
    }
};
class Solution {
  public:
    int MaxConnection(vector<vector<int>>& grid) {
        /**
         * Simpler version - 
         * 1. Use union-size than union-rank to track size of component
         * 2. Traverse grid and make components
         * 3. For all zeroes, turn it into 1 and calculate the size of 1s component thus formed. Don't perform union. Do this for unique adj. parents
         * 4. Check in grid for every cell the parent size...just in case all elements were 1 or there were single node islands
         * 
         * Misconception: there can't be a case where turning 0->1 will not benefit the max. component, hence task 4 can be performed at last and not at 2.
        */
        // O(N*M) both time and space
        int n = grid.size(), m = grid[0].size();
        int xd[4] = {1,-1,0,0};
        int yd[4] = {0,0,1,-1};
        DisjointSet ds(n*m); // lineared the 2D array
        int ans = 0; // assuming no existence of 1
        
        vector<int> zeroIndices;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                int nodeNum = i*m + j;
                if(grid[i][j] == 0){
                    zeroIndices.push_back(nodeNum);
                    continue;
                }
                // We are constraining ans >= 2 (because we are dependent on 2 1s together)
                for(int z=0; z<4; z++){
                    int adjr = i + xd[z];
                    int adjc = j + yd[z];
                    if(adjr < 0 || adjr >= n || adjc < 0 || adjc >= m || grid[adjr][adjc] == 0)
                        continue;

                    int adjNodeNum = adjr * m + adjc;
                    int pNode = ds.findParent(nodeNum);
                    int pAdjNode = ds.findParent(adjNodeNum);
                    if(pNode == pAdjNode)
                        continue;
                    ds.unionBySize(pNode, pAdjNode);
                }   
            }
        }

        for(int nodeNum: zeroIndices){
            int row = nodeNum/n;
            int col = nodeNum%n;
            // assuming to switch this cell (0) to 1
            // adj. cells can belong to same component
            int sizeNewComp = 1; // adding this cell in count
            set<int> uniqueAdjCellParents;
            for(int z=0; z<4; z++){
                int adjr = row + xd[z];
                int adjc = col + yd[z];
                if(adjr < 0 || adjr >= n || adjc < 0 || adjc >= m || grid[adjr][adjc] == 0)
                        continue;

                int adjNodeNum = adjr * m + adjc;
                int pAdjNode = ds.findParent(adjNodeNum);
                // parent of node and adjNode can't be same as node is just turned 1
                uniqueAdjCellParents.insert(pAdjNode);
            }
            for(int pAdjNode: uniqueAdjCellParents){
                sizeNewComp += ds.getSize(pAdjNode);
            }
            ans = max(ans, sizeNewComp);
        }
        
        // For case where all elements are 1 or all islands are single node islands
        for(int cellNo = 0; cellNo < n*m; cellNo++){
            ans = max(ans, ds.getSize(ds.findParent(cellNo)));
        }
        return ans;
    }
};

// Solution 2: no in one go, but with retrospective checks
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
    int getSize(int u){
        return size[u];
    }
};
class Solution {
  public:
    int MaxConnection(vector<vector<int>>& grid) {
        // Union-find isn't beneficial for this problem
        // Track connected 1's components by union-size -> store max. 1's component size in variable
        // Now for every 0 check what will be the max. size of generated 1's component would be after turning it to 1
        // Compare with the value store else update it.
        // Do this for all 0s and return the max ans

        // NOTE: count for unique components around 0. Count for single existence of 1 in grid. Tracking max 1s component from beginning
        int n = grid.size(), m = grid[0].size();
        int xd[4] = {1,-1,0,0};
        int yd[4] = {0,0,1,-1};
        DisjointSet ds(n*m); // lineared the 2D array
        int max1sComponentSize = 0;
        
        // O(N*M*4c)
        vector<int> zeroIndices;
        for(int i=0; i<n; i++){
            for(int j=0; j<m; j++){
                int nodeNum = i*m + j;
                if(grid[i][j] == 0){
                    zeroIndices.push_back(nodeNum);
                    continue;
                } else { 
                    //-----NOTE----------
                    // not putting this else would constrain max1sComponentSize >= 2 
                    max1sComponentSize = max(max1sComponentSize, 1);
                }
                for(int z=0; z<4; z++){
                    int adjr = i + xd[z];
                    int adjc = j + yd[z];
                    if(adjr < 0 || adjr >= n || adjc < 0 || adjc >= m || grid[adjr][adjc] == 0)
                        continue;

                    int adjNodeNum = adjr * m + adjc;
                    int pNode = ds.findParent(nodeNum);
                    int pAdjNode = ds.findParent(adjNodeNum);
                    if(pNode == pAdjNode)
                        continue;
                    ds.unionBySize(pNode, pAdjNode);
                    //-----NOTE----------
                    max1sComponentSize = max(max1sComponentSize, max(ds.getSize(pNode), ds.getSize(pAdjNode)));
                }   
            }
        }

        // Till here no cell is turned 1 from 0. We have max. 1s component island size in max1sComponentSize
        // O(N*M*4c)
        for(int ind: zeroIndices){
            int row = ind/n;
            int col = ind%n;
            // assuming to switch this cell (0) to 1
            // adj. cells can belong to same component
            int size1sComponent = 1; // considering this cell as sole component
            set<int> uniqueAdjCellParents;
            for(int z=0; z<4; z++){
                int adjr = row + xd[z];
                int adjc = col + yd[z];
                if(adjr < 0 || adjr >= n || adjc < 0 || adjc >= m || grid[adjr][adjc] == 0)
                        continue;

                int adjNodeNum = adjr * m + adjc;
                int pAdjNode = ds.findParent(adjNodeNum);
                // parent of node and adjNode can't be same as node is just turned 1
                uniqueAdjCellParents.insert(pAdjNode);
            }
            //-----NOTE----------
            for(int pAdjNode: uniqueAdjCellParents){
                size1sComponent += ds.getSize(pAdjNode);
            }
            // count of the 1s component thus formed is here. Comparing with max1sComponentSize to get max. possible 1s component
            max1sComponentSize = max(max1sComponentSize, size1sComponent);
        }
        return max1sComponentSize;
    }
};