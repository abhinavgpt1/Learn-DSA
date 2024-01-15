/**
 * Prim's Algo
 * -----------
 * 
 * @copyright Copyright (c) 2024
 * 
 */

// Solution 1: ElogV, just like dijkstra
class Solution{
    public:
	//Function to find sum of weights of edges of the Minimum Spanning Tree.
    int spanningTree(int V, vector<vector<int>> adj[]) {
        // starting point be 0
        vector<int> dist(V, INT_MAX); //min dist to reach a node from its adj. nodes
        dist[0] = 0;
        set<pair<int, int>> pending; //dist, node
        pending.insert({dist[0], 0});
        
        vector<bool> visited(V, false);
        // always a connected graph
        // O(ElogV)
        // coding ninjas way i.e. using visited array takes O(V^2) ~ O(V^2 + E)
        
        int spanningTreeWeight = 0;
        while(!pending.empty()){
            auto it = pending.begin();
            pending.erase(it);
            
            int distNode = it->first;
            int node = it->second;
            visited[node] = true; //the node is ready for updation by any other node unless popped from set
            spanningTreeWeight += distNode;
            
            for(vector<int> edge: adj[node]){
                int adjNode = edge[0];
                int adjNodeWeight = edge[1];
                
                // This visisted check is present here and not in dijkstra because the distNode can be updated leading to discontinuity in spanning tree under formation
                // In Dijkstra it was not possible as the distNode is a min. cumulative sum of edgeWeights connecting it to src, which would not update once the min. is reached 
                if(visited[adjNode]) 
                    continue;
                else if(dist[adjNode] > adjNodeWeight){
                    if(dist[adjNode] != INT_MAX)
                        pending.erase({dist[adjNode], adjNode});
                    dist[adjNode] = adjNodeWeight;
                    pending.insert({dist[adjNode], adjNode});
                }
            }
        }
        return spanningTreeWeight;
    }
};

// Solution 2: Coding ninjas way to use visited array leading to O(V^2) - refer coding ninjas directory>Graph CW