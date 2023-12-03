//another way of checking cycle is to keep 2 arrays of size V
// 1. visited which tracks what all nodes are visited atlease once - exactly the purpose of my soln.s isNotCyclic
// 2. dfsVisited which tracks what all nodes are visited in a single directed traversal run - exactly same as visited array of my soln.
// striver's video on directed graph cycle detection
// https://www.youtube.com/watch?v=uzVUw90ZFIg&list=PLgUwDviBIf0rGEWe64KWas0Nryn7SCRWw&index=11

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
