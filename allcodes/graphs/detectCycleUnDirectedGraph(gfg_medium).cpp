class Solution {
  public:
    // Function to detect cycle in an undirected graph.
    bool isCyclicComponent(vector<int> adj[], int index, int parent, vector<bool> &visited) {
        visited[index] = true;
        for(int i = 0; i < adj[index].size(); i++){
            int child = adj[index][i];
            if(child == parent)
                continue;
            if(visited[child] || isCyclicComponent(adj, child, index, visited))
                return true;
        }
        return false;
    }
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool> visited(V, false);
        //components in graph need to be handled this way - explicitly
        for(int i=0; i<V; i++){
            if(!visited[i] && isCyclicComponent(adj, i, -1, visited))
                return true;
        }
        return false;
    }
};
// time complexity = O(V+E) = overall loop over vertices run and on edges - 
    // vertices on line 18 : to check if they are visited or not and then to run dfs on the,
    // edges in total all are visited after exhaustive run on graph via isCyclicComponent function
// space = O(V)