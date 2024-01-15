/**
 * Articulation Point - I
 * ----------------------
 * Given an undirected connected graph with V vertices and adjacency list adj. 
 * You are required to find all the vertices removing which (and edges through it) disconnects the graph into 2 or more components and return it in sorted manner.
 * Note: Indexing is zero-based i.e nodes numbering from (0 to V-1). There might be loops present in the graph.
 * 
 */

// AP is for Undirected Graph, because components make sense in undirected graph
class Solution {
    void dfs(int index, int parent, int timer, vector<int>adj[], vector<bool> &visited, vector<int> &tin, vector<int> &low, map<int, bool> &isAP){
        visited[index] = true;
        tin[index] = low[index] = timer;
        int children=0;
        for(int v: adj[index]){
            if(v == parent) // no updations from parent whatsoever
                continue;
            if(!visited[v]){
                dfs(v, index, timer + 1, adj, visited, tin, low, isAP);
                if(low[v] >= tin[index] && parent != -1){
                    // v can't reach beyond index, hence qualifying index as an AP
                    isAP[index] = true;
                    continue;
                }
                // ref: https://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/
                // Check if the subtree rooted with v has
                // a connection to one of the ancestors of u
                low[index] = min(low[index], low[v]); // IMP
                children++;// checks components along branch
                
            } else{
                // Update low value of u for parent function calls.
                // Clearly, the 'v' got visited by parent of u or parents of it, so we want to find an alternative way/time to reach ancestor of 'v'
                // we take the start time of adj. nodes and not min. time, just because at v's removal the min. time/node might be unreachable by index
                low[index] = min(low[index], tin[v]);
            }
        }
        if(children >= 2 && parent == -1)
            isAP[index] = true;
    }
  public:
    vector<int> articulationPoints(int V, vector<int>adj[]) {
        map<int, bool> isAP;
        vector<bool> visited(V, false);
        vector<int> tin(V), low(V);
        for(int i=0; i<V; i++){
            if(!visited[i])
                dfs(i, -1, 1, adj, visited, tin, low, isAP);
        }
        vector<int> ans;
        for(auto p: isAP)
        if(p.second)
            ans.push_back(p.first);
        if(ans.empty())
            return {-1};
        return ans;
    }
};