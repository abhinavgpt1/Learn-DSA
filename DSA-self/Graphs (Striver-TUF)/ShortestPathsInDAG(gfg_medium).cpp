/**
 * Given a Directed Acyclic Graph of N vertices from 0 to N-1 
 * and a 2D Integer array(or vector) edges[ ][ ] of length M, 
 * where there is a directed edge from edge[i][0] to edge[i][1] with a distance of edge[i][2] for all i.
 * 
 * Find the shortest path from src(0) vertex to all the vertices 
 * and if it is impossible to reach any vertex, then return -1 for that vertex.
 * 
 */

// (1) Alternative Solution - traverse nodes based on topoSort
// Looks doubtful to me, since dijkstra like algo(below) selects nodes based on min distance from src
// whereas topoSort doesn't have a take weight of edges into account while providing a traversal sequence -> TopoSort is good for scheduling algos only
// Although it may sound fine that elements in topoSort will be picked in the same manner as dijkstra, but there can be loopholes

// (2) DFS is an exponential soln. and will TLE

class Solution {
    // Well separation of concerns
    int findReachableMinNode(vector<int> &dist, vector<bool> &visited, int N){
        int minNode = -1;
        for(int i=0; i<N; i++){
            if(!visited[i] && (minNode == -1 || dist[i] < dist[minNode]))
                minNode = i;
        }
        if(minNode != -1 && dist[minNode] == INT_MAX) // checks if reachable, else returns -1
            return -1;
        return minNode; //can return -1 if overused (beyond N times)
    }
    vector<int> sssp(vector<vector<pair<int, int>>> &graph, int N, int src){
        vector<bool> visited(N, false);
        vector<int> dist(N, INT_MAX);
        dist[src] = 0;
        
        for(int i=0; i<N; i++){
            int node = findReachableMinNode(dist, visited, N); //finds minimum distance node from src as they get visited
            if(node == -1) // As soon as there are no reachable nodes, we break
                break;
            visited[node] = true;
            for(pair<int, int> v: graph[node]){
                if(!visited[v.first] && (dist[node] + v.second < dist[v.first])){
                    dist[v.first] = dist[node] + v.second;
                }
            }
        }
        for(int i=0; i<N; i++){
            if(dist[i] == INT_MAX)
                dist[i] = -1;
        }
        return dist;
    }
  public:
     vector<int> shortestPath(int N,int M, vector<vector<int>>& edges){
        vector<vector<pair<int, int>>> graph(N);
        for(int i=0; i<M; i++){
            graph[edges[i][0]].push_back({edges[i][1], edges[i][2]});
        }
        return sssp(graph, N, 0); //single source shortest path
    }
};

// Solution with dist initialised to -1
// User function Template for C++
class Solution {
    int findMinNode(int V, vector<int> &distance, vector<bool> &visited){
        int minIndex = -1;
        for(int i=0; i<V; i++){
            if(distance[i] != -1 && !visited[i] && (minIndex == -1 || distance[i] < distance[minIndex]))
                minIndex = i;
        }
        return minIndex;
    }
    void SSSP(int V, vector<vector<pair<int, int>>> &graph, vector<bool> &visited, set<int> &onceVisited, vector<int> &distance, int src){
        
        for(int i=1; i<=V; i++){ // last loop is redundant, since last vertex in process can't change distance of any node since rest will be visited already
            int index = findMinNode(V, distance, visited);

            if(index == -1 || !onceVisited.count(index))
                return;
            
            visited[index] = true;
            for(auto pp: graph[index]){
                if(distance[pp.first] == -1 || distance[pp.first] > distance[index] + pp.second)
                    distance[pp.first] = distance[index] + pp.second;
                onceVisited.insert(pp.first);
            }
        }
    }
  public:
     vector<int> shortestPath(int N,int M, vector<vector<int>>& edges){
        // little complicated, but the only way to avoid INT_MAX as intialization
        int src = 0;
        vector<bool> visited(N, false);
        vector<int> distance(N, -1); // distance for unreachable nodes = -1
        set<int> onceVisited;
        vector<vector<pair<int, int>>> graph(N);
        for(auto x: edges){
            graph[x[0]].push_back({x[1], x[2]});
        }
        distance[src] = 0;
        onceVisited.insert(src);
        SSSP(N, graph, visited, onceVisited, distance, src);
        
        return distance;
    }
};