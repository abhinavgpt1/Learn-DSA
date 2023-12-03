//another way of checking cycle is to keep 2 arrays of size V
// 1. visited which tracks what all nodes are visited atlease once - exactly the purpose of my soln.s isNotCyclic
// 2. dfsVisited which tracks what all nodes are visited in a single directed traversal run - exactly same as visited array of my soln.
// striver's video on directed graph cycle detection
// https://www.youtube.com/watch?v=uzVUw90ZFIg&list=PLgUwDviBIf0rGEWe64KWas0Nryn7SCRWw&index=11

// Solution 1
class Solution {
  public:
    bool hasCycle(vector<int> adj[], int index, vector<bool> &visited,  vector<bool> &isNotCyclic){
        
        visited[index] = true;
        for(int i=0; i<adj[index].size(); i++){
            
            int child = adj[index][i]; 
            if(isNotCyclic[child])
            continue;
            
            if(visited[child])
                return true;
            
            if(hasCycle(adj, child, visited, isNotCyclic))
                return true;
        }
        isNotCyclic[index] = true;
        visited[index] = false;
        return false;
    }
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        
        vector<bool> visited(V, false); //visit tracking for a directed path
        vector<bool> isNotCyclic(V, false); //keeps track of nodes in a component so that we don't run hasCycle again and again in the same component
        
        //components in graph will also get handled implictly this way
        //this loop is necessary as all nodes may not get visited (in a component) starting from an index (say 0)
        for(int i=0; i<V; i++){
            if(!isNotCyclic[i] && hasCycle(adj, i, visited, isNotCyclic))
            return true;
        }
        return false;
    }
};
// time complexity = O(V+E) = overall loop over vertices run and on edges - 
    // vertices on line 28 : to check if they are visited or not and then to run dfs on the,
    // edges in total all are visited after exhaustive run on graph via isCyclicComponent function
// space = O(V)

// Solution 2
class Solution {
    bool isCycle(vector<int> adj[], int index, vector<int> &visited){
        if(visited[index] == 1)
            return true;
        visited[index] = 1;
        for(int x: adj[index]){
            if(visited[x] == -1)
                continue;
            if(isCycle(adj, x, visited))
                return true;
        }
        visited[index] = -1;
        return false;
    }
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        vector<int> visited(V, 0);
        for(int i=0; i<V; i++){
            if(!visited[i] && isCycle(adj, i, visited))
                return true;
        }
        return false;
    }
};

// Solution 3 - Kahn's Algo
class Solution {
  public:
    // Function to detect cycle in a directed graph.
    bool isCyclic(int V, vector<int> adj[]) {
        //usign BFS - Kahn's algo - topological sort BFS
        
        //will work for components in graph
        
        // O(E)
        vector<int> indegree(V, 0);
        for(int i=0; i<V; i++){
            for(int j=0; j<adj[i].size(); j++){
                indegree[adj[i][j]]++;
            }
        }
        
        //O(V)
        queue<int> pending;
        for(int i=0; i<V; i++){
            if(indegree[i] == 0)
                pending.push(i);
        }
        
        int cnt = 0;
        
        // O(V + E) - not 2E since directed graph
        while(!pending.empty()){
            int front = pending.front();
            pending.pop();
            
            for(int i=0; i<adj[front].size(); i++){
                indegree[adj[front][i]]--;
                if(indegree[adj[front][i]] == 0)
                    pending.push(adj[front][i]);
            }
            cnt++;
        }
        //T(n) = O(V + E)
        //S(n) = O(V)
        return (cnt != V);
    }
};