/**
 * Given a Directed Graph with V vertices (Numbered from 0 to V-1) and E edges,
 * Find the number of strongly connected components in the graph.
 * 
 */

// Only for directed graph
class Solution
{
    void dfs(vector<vector<int>> &adj, vector<bool> &visited, stack<int> &visitedNodesStk, int index){
        visited[index] = true;
        for(int v: adj[index]){
            if(!visited[v])
                dfs(adj, visited, visitedNodesStk, v);
        }
        visitedNodesStk.push(index);
    }
	public:
	//Function to find number of strongly connected components in the graph.
    int kosaraju(int V, vector<vector<int>>& adj) {
        // O(V+E) for both space and time
        vector<bool> visited(V, false);
        stack<int> visitedNodesStk; // nodes in order of their finishing time (descending order)
        
        //Step1: put nodes in stack inorder of their visiting in reverse - called "Sort nodes according to its finish time"
        for(int i=0; i<V; i++){
            if(!visited[i])
                dfs(adj, visited, visitedNodesStk, i);
        }
        // Reason for such order is to prevent those SCCs(say Y) to not traverse SCCs(say X)
        // which were visited from X and didn't returned back. Because now after reversing the graph they will try to traverse X
        
        // Same goes other way around: if X is the one that is visited by Y, 
        // then traversal by X on graph reversal is alarming for Y, hence Y should be the one doing its traversal on reversal first
        // Hence, nodes of Y will be on top in stack than X
        
        // Step2: reverse the graph
        vector<vector<int>> adjRev(V);
        for(int i=0; i<V; i++){
            for(int v: adj[i]){
                adjRev[v].push_back(i);
            }
        }

        // Step3: Dfs again in order of nodes in stack
        visited.clear(); // makes size 0
        visited.resize(V, false); // works for new elements that are added post the size of vector intially
        int cnt = 0;
        stack<int> garbage; // visitedNodesStk could be used as the repeative elements would be visited by then
        while(!visitedNodesStk.empty()){
            int node = visitedNodesStk.top(); visitedNodesStk.pop();
            if(!visited[node]){
                // can return list of nodes visited = scc
                dfs(adjRev, visited, garbage, node);
                cnt++;
            }
        }
        return cnt;
    }
};