/**
 * There are n stones at some integer coordinate points on a 2D plane. 
 * Each coordinate point may have at most one stone.
 * You need to remove some stones. 
 * A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.
 * Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone, 
 * return the maximum possible number of stones that you can remove.
 * 
 */
// Solution 1: By some examples we'll know that a connected component of all stones by same row/column will give ans = 1. So (sum up the size of stones in component - number of components) = ans
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
    int maxRemove(vector<vector<int>>& stones, int n) {
        // ans seems to be (size of component - 1) for all components made over same row or col stone
        // Aim at tracking all stones which have same row or column
        // Component can be traced with straight lines along row or column, hence all but one stones can be removed
        map<int, int> stoneAtRow; //row index, stone index
        map<int, int> stoneAtCol; //col index, stone index
        DisjointSet ds(n);
        for(int i=0; i<n; i++){
            int sr = stones[i][0];
            int sc = stones[i][1];
            if(stoneAtRow.count(sr)){
                int p1 = ds.findParent(stoneAtRow[sr]);
                int p2 = ds.findParent(i); // always i
                if(p1 != p2){
                    ds.unionBySize(p1, p2);
                }
            }
            else {
                // the sole representative of row=sr is ith stone
                // anyone who lies on this row becomes part of this stone's parent
                stoneAtRow[sr] = i;
            }
            
            if(stoneAtCol.count(sc)){
                int p1 = ds.findParent(stoneAtCol[sc]);
                int p2 = ds.findParent(i); // always i
                if(p1 != p2){
                    ds.unionBySize(p1, p2);
                }
            }
            else {
                // the sole representative of col=sc is ith stone
                // anyone who lies on this column becomes part of this stone's parent
                stoneAtCol[sc] = i;
            }
        }
        // int ans = 0;
        // for(int i=0; i<n; i++){
        //     int stoneParent = ds.findParent(i);
            // if(stoneParent == i)
            //     ans += ds.getSize(stoneParent) - 1;
        // }
        // return ans;
        
        // above clubs to below code
        int components = 0;
        for(int i=0; i<n; i++){
            int stoneParent = ds.findParent(i);
            if(stoneParent == i)
                components++;
        }
        return n - components;
    }
};

// Solution 2: Striver's way to consider row and col as nodes and connect rowNum and colNum, where colNum = colNum(0-based) + maxRow + 1
// Very small code but one step ahead of above solution's intuition