/**
 * Number of Provinces
 * -------------------
 * Given an undirected graph with V vertices. We say two vertices u and v belong to a single province 
 * if there is a path from u to v or v to u. Your task is to find the number of provinces.
 * Note: A province is a group of directly or indirectly connected cities and no other cities outside of the group.
 * 
 */

// Solution 1: using disjoint sets (union by size strategy)
class DisjointSet{
    vector<int> parent, size;
    
    public:
    DisjointSet(int n){
        parent = vector<int>(n);
        size = vector<int>(n, 1);
        for(int i=0; i<n; i++)
            parent[i] = i;
    }
    int findParent(int x){
        if(x == parent[x])
            return x;
        return parent[x] = findParent(parent[x]); //path compression
    }
    void unionBySize(int x, int y){
        int px = findParent(x);
        int py = findParent(y);
        if(px == py)
            return;
        if(size[px] < size[py]){
            parent[px] = py;
            size[py] += size[px];
        } else{
            parent[py] = px;
            size[px] += size[py];
        }
    }
};
class Solution {
  public:
    int numProvinces(vector<vector<int>> adj, int V) {
        DisjointSet ds(V);
        for(int i=0; i<V; i++){
            for(int j=0; j<V; j++){
                if(!adj[i][j])
                    continue;
                ds.unionBySize(i, j);
            }
        }
        int ans = 0;
        for(int i=0; i<V; i++)
        {
            if(ds.findParent(i) == i)
                ans++;
        }
        return ans;
    }
};

// Solution 2: Find connected components by DFS/BFS
class Solution {
    void dfs(vector<vector<int>> &adjMatrix, vector<bool> &visited, int n, int index){
        visited[index]=true;
        for(int i=0; i<n; i++){
            if(adjMatrix[index][i] && !visited[i])
                dfs(adjMatrix, visited, n, i);
        }
    }
  public:
    int numProvinces(vector<vector<int>> adjMatrix, int V) {
        vector<bool> visited(V, false);
        int count = 0;
        for(int i=0; i<V; i++){
            if(!visited[i])
            {
                dfs(adjMatrix, visited, V, i);
                count++;
            }
        }
        return count;
    }
};