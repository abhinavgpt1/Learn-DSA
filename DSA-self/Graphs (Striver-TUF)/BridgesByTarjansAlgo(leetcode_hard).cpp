/**
 * Critical Connections in a Network
 * ---------------------------------
 * There are n servers numbered from 0 to n - 1 connected by undirected server-to-server connections forming a network where connections[i] = [ai, bi] represents a connection between servers ai and bi. 
 * Any server can reach other servers directly or indirectly through the network.
 * A critical connection is a connection that, if removed, will make some servers unable to reach some other server.
 * Return all critical connections in the network in any order.
 * 
 */

// Finding bridges make sense in undirected graph != finding SCC using Tarjans
// because components make sense in undirected graph
class Solution {
    void dfs(vector<vector<int>> &adj, vector<bool> &visited, vector<vector<int>> &bridges, vector<int> &visitingTime, vector<int> &adjNodeMinTime, int index, int parent, int timer){
        visited[index] = true;
        visitingTime[index] = adjNodeMinTime[index] = timer;
        for(int v: adj[index]){
            if(v == parent) // don't want to be updated by parent, as we want to check if parent or any other node can be visited through other route or in less time
                continue;
            if(!visited[v]){
                dfs(adj, visited, bridges, visitingTime, adjNodeMinTime, v, index, timer + 1);
                if(adjNodeMinTime[v] > visitingTime[index]){
                    bridges.push_back({index, v});
                    continue;
                }
                adjNodeMinTime[index] = min(adjNodeMinTime[index], adjNodeMinTime[v]);
            } else{
                // implies a loop is formed -> this edge can't be a bridge
                // GFG says, take min with tin[v] which is wrong -> [[0,1], [1, 2], [2, 3], [3, 0], [0, 4], [4, 5], [5, 2]] -> both as directed and undirected graph will give wrong ans if gfg statement is adopted
                adjNodeMinTime[index] = min(adjNodeMinTime[index], adjNodeMinTime[v]);
            }
        }
    }
public:
    vector<vector<int>> criticalConnections(int n, vector<vector<int>>& connections) {
        vector<vector<int>> adj(n);
        for(vector<int> edge: connections){
            adj[edge[0]].push_back(edge[1]);
            adj[edge[1]].push_back(edge[0]);
        }
        vector<bool> visited(n, false);
        vector<int> visitingTime(n);
        vector<int> adjNodeMinTime(n);
        vector<vector<int>> bridges;
        for(int i=0; i<n; i++){
            dfs(adj, visited, bridges, visitingTime, adjNodeMinTime, i, -1, 0);
        }
        return bridges;
    }
};