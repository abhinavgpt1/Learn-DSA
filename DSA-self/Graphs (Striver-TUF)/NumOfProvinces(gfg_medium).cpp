/**
 * Number of Provinces
 * -------------------
 * Given an undirected graph with V vertices. We say two vertices u and v belong to a single province 
 * if there is a path from u to v or v to u. Your task is to find the number of provinces.
 * Note: A province is a group of directly or indirectly connected cities and no other cities outside of the group.
 * 
 */

// Solution 1: using disjoint sets
class DisjointSet
{
    vector<int> rank; // measures the height of tree, ith node being the root
    vector<int> size; // measures the size of tree below it including itself
    vector<int> parent;

public:
    DisjointSet(int n)
    {
        // rank = vector<int>(n, 0);
        // parent = vector<int>(n);

        // better
        rank.resize(n, 0); // 0-based indexing
        size.resize(n, 1); // 0-based indexing
        parent.resize(n);  // 0-based indexing

        // resize(n+1) will work for 1-based indexing problems as well as 0-based
        for (int i = 0; i < n; i++)
        {
            parent[i] = i;
        }
    }
    int findParent(int u)
    {
        if (parent[u] == u)
            return u;
        return parent[u] = findParent(parent[u]); // path compression by assigning parent[u] to ultimate parent, otherwise its complexity is log(N)
    }
    void unionByRank(int u, int v)
    {
        int pu = findParent(u);
        int pv = findParent(v);
        if (pu == pv) // do not anything if u and v belong to same set
            return;
        int rankpu = rank[pu];
        int rankpv = rank[pv];

        if (rankpu < rankpv)
        {
            // pv is at higher level
            // parent[pu] = parent[pv]; // parent[pv] = pv, hence the call to find parent broke (and also that's the defintion of parent)
            parent[pu] = pv;
        }
        else if (rankpv < rankpu)
        {
            // pu is at higher level
            parent[pv] = pu;
        }
        else
        {
            parent[pv] = pu;
            rank[pu]++;
        }
        // rank is not a measurement of number of attachments, so it can only be updated when rank(u) == rank(v)
    }
    void unionBySize(int u, int v)
    {
        int pu = findParent(u);
        int pv = findParent(v);
        if (pu == pv) // do not anything if u and v belong to same set
            return;
        int sizepu = size[pu];
        int sizepv = size[pv];

        if (sizepu < sizepv)
        {
            parent[pu] = pv;
            size[pv] += sizepu;
        }
        else
        {
            parent[pv] = pu;
            size[pu] += sizepv;
        }
        // size of pu/pv is increased everytime, so no need of else-if
    }
    void printParentAndRankForNode()
    {
        for (int i = 0; i < parent.size(); i++)
        {
            cout << "for " << i << ", parent: " << parent[i] << ", rank: " << rank[i] << endl;
        }
    }
    void printParentAndSizeForNode()
    {
        for (int i = 0; i < parent.size(); i++)
        {
            cout << "for " << i << ", parent: " << parent[i] << ", size: " << size[i] << endl;
        }
    }
    void checkSameParent(int u, int v)
    {
        if (this->findParent(u) == this->findParent(v))
            cout << "yes, same parent: " << u << "," << v << endl;
        else
            cout << "no, not same parent: " << u << "," << v << endl;
    }
};
class Solution {
  public:
    int numProvinces(vector<vector<int>> adj, int V) {
        // same as find connected components of graph (DFS/BFS problem) - O(V+E) ~ O(V^2)
        DisjointSet ds(V);
        //traversing all edges - O(V^2) here
        for(int i=0; i<V; i++){
            for(int j=0; j<V; j++){
                if(adj[i][j] == 1){
                    
                    int pi = ds.findParent(i);
                    int pj = ds.findParent(j);
                    if(pi == pj)
                        continue;
                    ds.unionBySize(pi, pj);
                }
            }
        }
        
        set<int> provinces;
        //counting sets by fetching representative of each set
        for(int i=0; i<V; i++){
            provinces.insert(ds.findParent(i));// expensive
            // if(ds.findParent(i) == i)// less expensive
            //     cnt++;
            // if we could check parent[i] == i, it'll be best
        }
        return provinces.size();
    }
};

// Solution 2: Find connected components by DFS/BFS