/**
 * A Hamiltonian path, is a path in an undirected graph that visits each vertex exactly once. 
 * Given an undirected graph, the task is to check if a Hamiltonian path is present in it or not.
 * 
 * Extra-
 * ------
 * ref: https://stackoverflow.com/questions/49134720/hamiltonian-path-algorithm-time-complexity
 * A traversable graph is one you can draw without taking your pen off the paper, 
 * and without going over any edge twice.
 * Hence, Hamiltonian Path != Traversability (Euler Path or Circuit)
 * 
 */

class Solution{
 bool dfs(vector<vector<int>> &adj, vector<bool> &visited, int index, int remVertices){
        visited[index] = true;
        remVertices--; //burned 1 off rem vertices
        if(remVertices == 0) // all vertices visited in a single go
            return true;

        for(int v: adj[index]){ // N-1 * N-2 * .... * 1
            if(!visited[v]){
                if(dfs(adj, visited, v, remVertices))
                    return true;
            }
        }
        visited[index] = false;
        remVertices++;
        return false; 
    }
    public:
    bool check(int N,int M,vector<vector<int>> Edges) {
        vector<vector<int>> adj(N);
        for(int i=0; i<M; i++){ // O(N + E)
            adj[Edges[i][0] - 1].push_back(Edges[i][1] - 1);
            adj[Edges[i][1] - 1].push_back(Edges[i][0] - 1);
        }
        vector<bool> visited(N, false);
        for(int i=0; i<N; i++){ // O(N)
            if(dfs(adj, visited, i, N))
                return true;
        }
        return false;
    }
};