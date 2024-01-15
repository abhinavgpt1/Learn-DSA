/**
 * Kruskal's Algo
 * --------------
 * 
 * 
 */
// using sorting over list of edges than using PQ makes it efficient, yet same complexity
// halting process as soon as N-1 edges are consumed under MST also makes process efficient, yet same complexity
// Solution 1: Disjoint set fused with Solution class : UnionBySize is used
class Solution
{
    int findParent(int u, vector<int> &parent){ //imp. to pass by ref
        if(parent[u] == u)
            return u;
        return parent[u] = findParent(parent[u], parent);
    }
    void unionBySize(int pu, int pv, vector<int> &parent, vector<int> &size){
        int sizepu = size[pu];
        int sizepv = size[pv];
        if(sizepu < sizepv){
            parent[pu] = pv;
            size[pv] += size[pu];
        } else {
            parent[pv] = pu;
            size[pu] += size[pv];
        }
    }
	public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // disjoint set setup
        vector<int> size(V, 1);
        vector<int> parent(V);
        for(int i=0; i<V; i++)
            parent[i] = i;
            
        // kruskal's algo
        priority_queue<pair<int, pair<int, int>>, vector<pair<int, pair<int, int>>>, greater<pair<int, pair<int, int>>>> pending;
        // 2Elog2E
        for(int i=0; i<V; i++){
            //redundant insertion of same edge twice
            for(vector<int> vec: adj[i]){
                pending.push({vec[1], {i, vec[0]}});
            }
        }
        int cntEdges = 0;
        int sumWeightMST = 0;
        // 2E(log2E + 2c + c + c + c) ~ Elog2E ~ ElogE
        // Coding Ninjas solution would have (2c -> 2logV) => ElogEV therefore total complexity = ElogE + ElogEV = O(ElogEV)
        while(cntEdges < V && !pending.empty()){
            int edgeWeight = pending.top().first;
            int u = pending.top().second.first;
            int v = pending.top().second.second;
            pending.pop();
            
            int pu = findParent(u, parent);
            int pv = findParent(v, parent);
            if(pu == pv)
            // we can directly use unionBySize, but pu == pv check in unionBySize is a check by Union-Find Algo
            // but here the explicit check is a business rule, that we don't want to make cycle. It could have been something else like update pu/pv or something
                continue;
            unionBySize(pu, pv, parent, size);
            sumWeightMST += edgeWeight;
            cntEdges++;
        }
        return sumWeightMST;
    }
};