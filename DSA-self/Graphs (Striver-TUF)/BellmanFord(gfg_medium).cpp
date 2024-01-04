/*
 * Bellman-Ford Algo
 * -----------------
 * Given a weighted, directed and connected graph of V vertices and E edges.
 * Find the shortest distance of all the vertex's from the source vertex S. 
 * If a vertices can't be reach from the S then mark the distance as 10^8.
 * Note: If the Graph contains a negative cycle then return an array consisting of only -1.
 */


typedef long long int lli;
class Solution {
    const int INF = 1e8;
  public:
    /*  Function to implement Bellman Ford
    *   edges: vector of vectors which represents the graph
    *   S: source vertex to start traversing graph with
    *   V: number of vertices
    */
    
    /**Approach to Bellman-Ford is similar to Dijkstra with visited array and N-1 loops
     * In every loop:
     * a min node is generated (and is never relaxed later (implicitly))
     * all its edges are traversed. 
     * Here a little extra happens - all edges are traversed
    **/
   
    // Enhancement: Visited array to check if node was visited once - so that those cases don't fail when dist[x]=INF after getting visited. 
    // There should be constraint to some level in such case
    //T(n) = O(VE), S(n) = O(V)
    vector<int> bellman_ford(int V, vector<vector<int>>& edges, int S) {
        vector<lli> dist(V, INF);
        dist[S] = 0;
        
        //dist[x] can reach V(minEdge*E) = 5e2(-1e3*25e4) = -125e9 >> -INT_MIN
        //dist[x] belongs to [-125e9, 125e9]
        //We are interested in change in value of dist[x], but there can be repercussions due to rollover at Nth loop
        //using long long int for dist
        for(int i=0; i<V-1; i++){
            for(vector<int> edge: edges){
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];
                //relaxation can't be done by unvisited nodes
                //putting this check inside relaxation may result in wrong answer due to rollover, if INF=INT_MAX and w>0
                if(dist[u] == INF)
                    continue;
                if(dist[v] > dist[u] + w){
                    dist[v] = dist[u] + w;// relaxation of node 'v'
                }
            }
        }
        
        //Nth loop to check change in dist[i]
        for(vector<int> edge: edges){
            int u = edge[0];
            int v = edge[1];
            int w = edge[2];
            //unvisited nodes can't relax any node
            if(dist[u] == INF)
                continue;
            if(dist[v] > dist[u] + w){
                //negative cycle exists
                return vector<int>(1, -1);
            }
        }
        
        return vector<int>(dist.begin(), dist.end());
    }
};