/**
 * Connecting the graph
 * --------------------
 * 
 * You are given a graph with n vertices and m edges.
 * You can remove one edge from anywhere and add that edge between any two vertices in one operation.
 * Find the minimum number of operations that will be required to make the graph connected.
 * 
 * If it is not possible to make the graph connected, return -1.
 * 
 */

// Solution 1: Solvable using Disjoint set only
class DisjointSet{
    vector<int> size; // measures size of tree below a node including itself
    vector<int> parent; 
    public:
    DisjointSet(int n){
        size.resize(n, 1); // each node is in separate set initially
        parent.resize(n);
        for(int i=0; i<n; i++)
            parent[i] = i;
    }
    int findParent(int u){
        if(parent[u] == u)
            return u;
        return parent[u] = findParent(parent[u]);
    }
    void unionBySize(int u, int v){
        int pu = findParent(u);
        int pv = findParent(v);
        if(pu == pv)
            return;
        if(size[pu] < size[pv]){
            // pv is leader
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            // pu is leader
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
};
class Solution {
  public:
    int Solve(int n, vector<vector<int>> &edges) {
        // count connected components(c1) and count useless edges in forming a component(c2)
        // check if c1<=c2 return c1 else return -1
        DisjointSet ds(n);
        int uselessEdges = 0; //edges which do not add any new vertex to the component
        for(vector<int> edge: edges){
            int pu = ds.findParent(edge[0]);
            int pv = ds.findParent(edge[1]);
            if(pu == pv){
            // we can directly use unionBySize, but pu == pv check in unionBySize is a check by Union-Find Algo
            // but here the explicit check is a business rule, that we don't want to make cycle. It could have been something else like update pu/pv or something
                uselessEdges++;
                continue;
            }
            ds.unionBySize(pu, pv);
        }

        int provinces = 0;
        for(int i=0; i<n; i++){
            if(ds.findParent(i) == i)
                provinces++;
        }
        provinces--; //keeping one province aside to which other provinces will join
        if(provinces <= uselessEdges)
            return provinces;
        return -1;
    }
};