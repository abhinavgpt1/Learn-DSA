/**
 * Undirected Graph Cycle
 * ----------------------
 * Given an undirected graph with V vertices labelled from 0 to V-1 and E edges, check whether the graph contains any cycle or not.
 * The Graph is represented as an adjacency list, where adj[i] contains all the vertices that are directly connected to vertex i.
 * NOTE: The adjacency list represents undirected edges, meaning that if there is an edge between vertex i and vertex j, both j will be adj[i] and i will be in adj[j].
 *
 * Constraints:
 * 1 ≤ adj.size() ≤ 10^5
 *
 * Expected time complexity: O(V+E)
 * Expected space complexity: O(V)
 *
 */

// link: https://www.geeksforgeeks.org/problems/detect-cycle-in-an-undirected-graph/1
// article: https://www.geeksforgeeks.org/detect-cycle-undirected-graph/

// Solution 1: using DFS: O(V+2E), O(V)
class Solution
{
public:
    bool isCyclicComponent(vector<int> adj[], int index, int parent, vector<bool> &visited)
    {
        visited[index] = true;
        for (int i = 0; i < adj[index].size(); i++)
        {
            int child = adj[index][i];
            if (child == parent)
                continue;
            if (visited[child] || isCyclicComponent(adj, child, index, visited))
                return true;
        }
        //// alternative logic to above code
        // for (int i = 0; i < adj[index].size(); i++)
        // {
        //     int child = adj[index][i];
        //     if (!visited[child] && isCyclicComponent(adj, child, index, visited))
        //         return true;
        //     else if (child != parent)
        //         return true;
        // }
        return false;
    }
    bool isCycle(int V, vector<int> adj[])
    {
        vector<bool> visited(V, false);
        // components in graph need to be handled this way - explicitly
        for (int i = 0; i < V; i++)
        {
            if (!visited[i] && isCyclicComponent(adj, i, -1, visited))
                return true;
        }
        return false;
    }
};

// Solution 2: using BFS: O(V+2E), O(V)
class Solution {
    bool isCycleHelper(int V, vector<int> adj[], int startIndex, vector<bool> &visited) {
        queue<pair<int, int>> pending;
        pending.push({startIndex, -1});
        visited[startIndex] = true;
        while(!pending.empty()){
            int frontNode = pending.front().first;
            int frontParent = pending.front().second;
            pending.pop();
            for(int v: adj[frontNode]){
                if(visited[v]){
                    if(v != frontParent)
                        return true;
                    continue;
                }
                visited[v] = true;
                pending.push({v, frontNode});
            }
        }
        return false;
    }
  public:
    bool isCycle(int V, vector<int> adj[]) {
        vector<bool> visited(V, false);
        for(int i=0; i<V; i++){
            if(!visited[i] && isCycleHelper(V, adj, i, visited))
                return true;
        }
        return false;
    }
};

// less optimized solution
// Solution 3: using DFS: O(V+2E), O(2V)
class Solution
{
    bool dfs(vector<vector<int>> &adj, vector<bool> &visited, vector<int> &parent, int index)
    {
        visited[index] = true;
        for (int x : adj[index])
        {
            if (x == parent[index])
                continue;
            else if (visited[x])
                return true;
            else
            {
                parent[x] = index;
                if (dfs(adj, visited, parent, x))
                    return true;
            }
        }
        return false;
    }

public:
    bool isCycle(vector<vector<int>> &adj)
    {
        // using dfs
        int n = adj.size();
        vector<bool> visited(n, false);
        vector<int> parent(n, -1);
        // components
        for (int i = 0; i < n; i++)
        {
            if (!visited[i] && dfs(adj, visited, parent, i))
                return true;
        }
        return false;
    }
};