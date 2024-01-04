/**
 * City With the Smallest Number of Neighbors at a Threshold Distance
 * ------------------------------------------------------------------
 * There are n cities numbered from 0 to n-1. 
 * Given the array edges where edges[i] = [fromi , toi ,weighti] represents 
 * a bidirectional and weighted edge between cities fromi and toi, and given the integer distance Threshold. 
 * You need to find out a city with the smallest number of cities that are reachable through some path and whose distance is at most Threshold Distance.
 * If there are multiple such cities, our answer will be the city with the greatest number.
 * 
 * Note: that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path. 
 * 
 * Expected Time Complexity: O(V^2 + EVlogV)
 * Expected Auxiliary Space:  O(N^3)
 * 
 * 
 * Constraints:
 * 1 ≤ N≤ 100
 * 1 <= edges.length <= n*(n-1)/2
 * edges[i].length == 3
 * 0 <= fromi < toi < n
 * 1 <= weight, distanceThreshold <= 10^4
 * All pairs (fromi, toi) are distinct
 */
class Solution {
    vector<int> dijkstra(vector<vector<pair<int, int>>> &graph, int n, int src){
        vector<int> dist(n, INT_MAX); //dist from src
        dist[src] = 0;
        set<pair<int, int>> pending; //dist, node
        pending.insert({dist[src], src});
        while(!pending.empty()){
            auto it = pending.begin();
            pending.erase(it);
            
            int distNode = it->first;
            int node = it->second;
            
            for(pair<int, int> pp: graph[node]){
                if(dist[pp.first] > dist[node] + pp.second) {
                    if(dist[pp.first] != INT_MAX){
                        pending.erase({dist[pp.first], pp.first});
                    }
                    dist[pp.first] = dist[node] + pp.second;
                    pending.insert({dist[pp.first], pp.first});
                }
            }
        }
        return dist;
    }
  public:
    int findCity(int n, int m, vector<vector<int>>& edges, int distanceThreshold) {
        // Weight is > 0, so V times Dijkstra can be used, which yields O(VElogV)
        // Counting number of cities with distance <= threshold is O(V) for a single node, resulting in O(V^2) if run for all nodes
        vector<vector<pair<int, int>>> graph(n);
        for(vector<int> edge: edges){
            graph[edge[0]].push_back({edge[1], edge[2]});
            graph[edge[1]].push_back({edge[0], edge[2]});
        }
        vector<vector<int>> minDist;
        for(int i=0; i<n; i++){
            minDist.push_back(dijkstra(graph, n, i));
        }
        int cityWithMinCitiesWithinThreshold = -1;
        int minCitiesWithinThresholdCnt = INT_MAX;
        for(int i=0; i<n; i++){
            int cntCitiesWithinThreshold = 0;
            for(int dist: minDist[i]){
                if(dist <= distanceThreshold)
                    cntCitiesWithinThreshold++;
            }
            if(minCitiesWithinThresholdCnt > cntCitiesWithinThreshold){
                minCitiesWithinThresholdCnt = cntCitiesWithinThreshold;
                cityWithMinCitiesWithinThreshold = i;
            } else if(minCitiesWithinThresholdCnt == cntCitiesWithinThreshold) {
                cityWithMinCitiesWithinThreshold = i; //taking city with higher number
            }
        }
        return cityWithMinCitiesWithinThreshold;
    }
};